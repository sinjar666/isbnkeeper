#include "readean13.h"

ReadEAN13::ReadEAN13(QString arg,QObject *parent) :
    QThread(parent)
{
    imgpath = new QString(arg);
}

void ReadEAN13::run()   {
    this->sleep(4);
    qDebug() << "Thread started.";
    initialize();
    r=400;
    getLimits();
    prepare();
    for(offset=0;offset<=9;offset++)    {
        curr_pos=0;
        d1=sum_odd=sum_even=last_digit=0;
        bool status=read2to7();
        status &= read8to13();
        result=QString::number(d1=(uint)patt.value(leftpatt)) + result;
        status &= check();
        if(status)  {
            qDebug() << "Checksum verified.";
            break;
        }
        else    {
            //qDebug() << "false at " << offset;
            result="";
            leftpatt="";
        }
    }
    qDebug()<< "End of thread exec";

}

void ReadEAN13::initialize()    {
    //const unsigned char code1A[] = {13,25,19,61,35,49,47,59,55,11};
    code1A[13]=0;
    code1A[25]=1;
    code1A[19]=2;
    code1A[61]=3;
    code1A[35]=4;
    code1A[49]=5;
    code1A[47]=6;
    code1A[59]=7;
    code1A[55]=8;
    code1A[11]=9;


    //const unsigned char code1B[] = {39,51,27,33,29,57,05,17,9,23};
    code1B[39]=0;
    code1B[51]=1;
    code1B[27]=2;
    code1B[33]=3;
    code1B[29]=4;
    code1B[57]=5;
    code1B[5]=6;
    code1B[17]=7;
    code1B[9]=8;
    code1B[23]=9;

    //const unsigned char code2[] = {114,102,108,66,92,78,80,68,72,116};
    code2[114]=0;
    code2[102]=1;
    code2[108]=2;
    code2[66]=3;
    code2[92]=4;
    code2[78]=5;
    code2[80]=6;
    code2[68]=7;
    code2[72]=8;
    code2[116]=9;


    patt["AAAAAA"]=0;
    patt["AABABB"]=1;
    patt["AABBAB"]=2;
    patt["AABBBA"]= 3;
    patt["ABAABB"]= 4;
    patt["ABBAAB"] =5;
    patt["ABBBAA"] =6;
    patt["ABABAB"]=7;
    patt["ABABBA"]=8;
    patt["ABBABA"]=9;


    src.load(*imgpath);
    QImage img=src.scaled(1024,768,Qt::KeepAspectRatio);
    for (int i = 0; i < img.width(); ++i)
        {
            for (int j = 0; j < img.height(); ++j)
            {
                QRgb col = img.pixel(i, j);
                int gray = qGray(col);
                img.setPixel(i, j, qRgb(gray, gray, gray));
            }
        }
    img=img.convertToFormat(QImage::Format_Indexed8);
    int t=100,t_old=0;
    QSet<int> G1,G2;
    while(t_old!=t) {
        G1.clear();
        G2.clear();
        t_old=t;
            for(int i=0;i<img.height();i++) {
                for(int j=0;j<img.width(); j++) {
                    if(qRed(img.pixel(j,i)) > t)
                        G1.insert(qRed(img.pixel(j,i)));
                    else
                        G2.insert(qRed(img.pixel(j,i)));
                }
            }
        int x,sum1=0,sum2=0;
        foreach(x,G1)
            sum1+=x;
        sum1/=G1.size();
        foreach(x,G2)
            sum2+=x;
        sum2/=G2.size();
        t=(sum1+sum2)/2;
    }
    qDebug() << "Threshold="<< t;
    binary = QImage(1024,768,QImage::Format_Mono);
    for(int i=0;i<img.width();i++) {
        for(int j=0;j<img.height();j++)  {
            int val=qRed(img.pixel(i,j));
            if(val<=t)
                binary.setPixel(i,j,0);
            else
                binary.setPixel(i,j,1);
        }
    }
//    QFile fil("out.jpg");
//    img.save(&fil);
//    fil.close();
}

void ReadEAN13::getLimits() {
    uint num_1l=0,max_1l=0,num_1r=0,max_1r=0,start_pos,end_pos;
    for(int i=511,j=511;i>=0;i--,j++) {
        if(qRed(binary.pixel(i,r))==0 || (i==0 && qRed(binary.pixel(i,r))!=0)) {
            if(num_1l>max_1l) {
                max_1l=num_1l;
                start_pos=i+max_1l+1;
            }
            num_1l=0;
        }
        else
            num_1l++;
        if(qRed(binary.pixel(j,r))==0 || (i==0 && qRed(binary.pixel(j,r))!=0)) {
            if(num_1r>max_1r)   {
                max_1r=num_1r;
                end_pos=j-max_1r-1;
            }
            num_1r=0;
        }
        else num_1r++;
    }
    left=start_pos;
    right=end_pos;
    qDebug()<<left << right;
//    bit_width = (right-left+1)/95;
//    qDebug()<< bit_width;
}

void ReadEAN13::prepare()   {
    tmp=QImage(right-left+1,100,QImage::Format_Mono);
    for(uint i=0;i<=right-left;i++)    {
        for(uint j=0;j<100;j++)   {
            if(qRed(binary.pixel(left+i,r+j))==0)
                tmp.setPixel(i,j,0);
            else
                tmp.setPixel(i,j,1);
        }
    }

    tmp=tmp.scaled(950,100,Qt::IgnoreAspectRatio);
    for(int i=0;i<950;i++)  {
        uint num0=0,num1=0,bit=0;
        for(int j=0;j<100;j++)  {
            if(qRed(tmp.pixel(i,j))==0)
                num0++;
            else num1++;
        }
        if(num1>num0) bit=1;
        else bit=0;
        for(int j=0;j<100;j++)  {
            tmp.setPixel(i,j,bit);
        }
    }
//    QFile fil2("out2.bmp");
//    fil2.open(QIODevice::WriteOnly| QIODevice::Truncate);
//    tmp.save(&fil2);
//    fil2.close();

}

bool ReadEAN13::readBit()  {
        if(qRed(tmp.pixel(curr_pos+offset,0))==0)   {
             curr_pos+=10;
             return true;
        }
        else    {
             curr_pos+=10;
             return false;
        }
}

uchar ReadEAN13::readBlock()    {
    uchar digit=0;
    for(int i=6;i>=0;i--)    {
        bool bit=readBit();
        //qDebug() << (bit?"1":"0");
        if(bit) digit |= (1<<i);
    }
    return digit;
}

bool ReadEAN13::read2to7()  {
    //First Read left guard --> 101
    if(!readBit())    {
        //qDebug()<<"here 1";
            return false;
    }
    if(readBit())   {
        //qDebug() << "here 10";
        return false;
    }
    if(!readBit())  {
        //qDebug() << "here101";
        return false;
    }

    for(int i=2;i<=7;i++)   {
        uchar block=readBlock();
        if(code1A.contains(block))  {
            uint val=(uint)code1A.value(block);
            result+=QString::number(val);
            if(i%2==0) sum_even+=val;
            else sum_odd+=val;
            leftpatt += "A";
        }
        else if(code1B.contains(block)) {
            uint val=(uint)code1B.value(block);
            result+=QString::number(val);
            if(i%2==0) sum_even+=val;
            else sum_odd+=val;
            leftpatt += "B";
        }
        else    {
            //        qDebug() << "stuck." << i;
            return false;
        }
    }
    return true;

}

bool ReadEAN13::read8to13() {
    //First read middle guard --> 01010
    if(readBit()) return false;
    if(!readBit()) return false;
    if(readBit()) return false;
    if(!readBit()) return false;
    if(readBit()) return false;

    for(int i=8;i<=13;i++)  {
        uchar block = readBlock();
        if(code2.contains(block))   {
            uint val=(uint)code2.value(block);
            result += QString::number(val);
            if(i%2==0) sum_even+=val;
            else if(i!=13) sum_odd+=val;
            else last_digit=val;
        }
        else    {
            //qDebug() << "STuck at" << i;
            return false;
        }
    }
    //Now finally read Right guard --> 101
    if(!readBit()) return false;
    if(readBit()) return false;
    if(!readBit())  {
        //qDebug("stuck.");
        return false;
    }
    qDebug() << "Right guard read.";
    return true;
}

bool ReadEAN13::check()     {
    if(((sum_even*3)+sum_odd+d1+last_digit)%10==0) {
        return true;
    }
    else return false;
}

QString ReadEAN13::getResult()  {
    return result;
}
