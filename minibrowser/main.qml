
import QtQuick 2.2
import QtQuick.Controls 1.1
import QtWebView 1.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2


ApplicationWindow {
    property bool showProgress: webView.loading
                                && Qt.platform.os !== "ios"
                                && Qt.platform.os !== "winrt"
    visible: true
    x: initialX
    y: initialY
    width: initialWidth
    height: initialHeight
    title: webView.title

    TextInput {
        id: date
        color: "#151515"; selectionColor: "green"
        font.pixelSize: 16; font.bold: true
        width: parent.width-16
        maximumLength: 16
        anchors.centerIn: parent
        focus: true
    }

    TextInput {
        id: timeinput
        x: -258
        y: -181
        width: 171
        height: 20
        text: qsTr("Text Input")
        font.pixelSize: 12
    }

    TextInput {
        id: vehicleno
        x: -258
        y: -181
        width: 171
        height: 20
        text: qsTr("Text Input")
        font.pixelSize: 12
    }

    TextInput {
        id: vehiclemodel
        x: -258
        y: -181
        width: 171
        height: 20
        text: qsTr("Text Input")
        font.pixelSize: 12
    }


    statusBar: StatusBar {
        id: statusBar
        visible: showProgress
        RowLayout {
            anchors.fill: parent
            Label { text: webView.loadProgress == 100 ? qsTr("Done") : qsTr("Loading: ") + webView.loadProgress + "%" }
        }
    }

    WebView {
        id: webView
        anchors.fill: parent
        url: initialUrl
        onLoadingChanged: {
            if (loadRequest.errorString)
                console.error(loadRequest.errorString);
        }
    }


}
