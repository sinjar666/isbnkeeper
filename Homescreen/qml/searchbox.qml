import Qt 4.7

Rectangle {
    id: box
    signal keyPressed(string searchText)
    width: 300
    height: 40
    Rectangle   {
        id: icon
        width: 50
        height: box.height
        Image   {
            id: icon_img
            smooth: true
            width: 40
            height: 40
            fillMode: Image.PreserveAspectCrop
            source: "Search-icon.png"
        }
    }

    TextInput {
        id: text_input1
        x:40
        width: parent.width-icon.width
        height: 40
        text: ""
        color: "black"
        horizontalAlignment: TextInput.AlignLeft
        font.strikeout: false
        readOnly: false
        font.pixelSize: 25
        echoMode: TextInput.Normal
        transformOrigin: Item.Left
        selectionColor: "#eca712"
        cursorVisible: false
        anchors.top: parent.top
        anchors.topMargin: 0
        font.family: "Liberation Sans Narrow"
        onTextChanged: box.keyPressed(text_input1.text)
    }


}
