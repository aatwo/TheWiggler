import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("The Wiggler")
    Component.onCompleted: init()

    property bool wigglerCoreIsRunning: false
    property int buttonAreaHeight: 40

    function init()
    {
        loadCurrentWiggleData()
    }

    function loadCurrentWiggleData()
    {
        const wiggleData = wiggleCore.getWiggleData()
        loadWiggleData(wiggleData)
    }

    function loadWiggleData(wiggleData)
    {
        wigglerCoreIsRunning = wiggleData.IsRunning
        wigglerIntervalEdit.value = wiggleData.WiggleIntervalMs
        wigglerDurationEdit.value = wiggleData.WiggleDurationMs
        horizontalMoveDistanceEdit.value = wiggleData.HorizontalMoveDistancePixels
        verticalMoveDistanceEdit.value = wiggleData.VerticalMoveDistancePixels
        alternateHorizontalDirectionEdit.checked = wiggleData.FlipHorizontalDirection
        alternateVerticalDirectionEdit.checked = wiggleData.FlipVerticalDirection
        moveHorizontallyEdit.checked = wiggleData.MoveHorizontal
        moveVerticallyEdit.checked = wiggleData.MoveVertical
    }

    function getWiggleDataFromUI()
    {
        let wiggleData = wiggleDataFactory.make()

        wiggleData.WiggleIntervalMs = wigglerIntervalEdit.value
        wiggleData.WiggleDurationMs = wigglerDurationEdit.value
        wiggleData.IsRunning = true
        wiggleData.HorizontalMoveDistancePixels = horizontalMoveDistanceEdit.value
        wiggleData.VerticalMoveDistancePixels = verticalMoveDistanceEdit.value
        wiggleData.FlipHorizontalDirection = alternateHorizontalDirectionEdit.checked
        wiggleData.FlipVerticalDirection = alternateVerticalDirectionEdit.checked
        wiggleData.MoveHorizontal = moveHorizontallyEdit.checked
        wiggleData.MoveVertical = moveVerticallyEdit.checked

        return wiggleData
    }

    ScrollView {
        x: 0
        y: 0
        width: parent.width
        height: parent.height - buttonAreaHeight

        Column {

            enabled: !wigglerCoreIsRunning
            padding: 20
            spacing: 20

            GroupBox {
                title: "General"
                Column {
                    spacing: 20
                    Row {
                        spacing: 20
                        Label {
                            text: "Wiggle interval"
                        }
                        SpinBox {
                            id: wigglerIntervalEdit
                            from: 0
                            to: 1000 * 60 * 60 // One hour
                            editable: true
                        }
                        Label {
                            text: "ms"
                        }
                    }

                    Row {
                        spacing: 20
                        Label {
                            text: "Wiggle duration"
                        }
                        SpinBox {
                            id: wigglerDurationEdit
                            from: 0
                            to: 1000 * 60 * 60 // One hour
                            editable: true
                        }
                        Label {
                            text: "ms"
                        }
                    }
                }
            }

            GroupBox {
                title: "Horizontal movement"
                Column {
                    spacing: 20
                    Row {
                        spacing: 20
                        Label {
                            text: "Move horizontally"
                        }
                        CheckBox {
                            id: moveHorizontallyEdit
                        }
                    }
                    Row {
                        spacing: 20
                        enabled: moveHorizontallyEdit.checked
                        Label {
                            text: "Horizontal move distance"
                        }
                        SpinBox {
                            id: horizontalMoveDistanceEdit
                            from: 0
                            to: 30000
                            editable: true
                        }
                        Label {
                            text: "pixels"
                        }
                    }

                    Row {
                        spacing: 20
                        enabled: moveHorizontallyEdit.checked
                        Label {
                            text: "Alternate horizontal direction"
                        }
                        CheckBox {
                            id: alternateHorizontalDirectionEdit
                        }
                        Label {
                            text: "pixels"
                        }
                    }
                }
            }

            GroupBox {
                title: "Vertical params"
                Column {
                    spacing: 20
                    Row {
                        spacing: 20
                        Label {
                            text: "Move vertically"
                        }
                        CheckBox {
                            id: moveVerticallyEdit
                        }
                    }
                    Row {
                        spacing: 20
                        enabled: moveVerticallyEdit.checked
                        Label {
                            text: "Vertical move distance"
                        }
                        SpinBox {
                            id: verticalMoveDistanceEdit
                            from: 0
                            to: 30000
                            editable: true
                        }
                        Label {
                            text: "pixels"
                        }
                    }

                    Row {
                        spacing: 20
                        enabled: moveVerticallyEdit.checked
                        Label {
                            text: "Alternate vertical direction"
                        }
                        CheckBox {
                            id: alternateVerticalDirectionEdit
                        }
                        Label {
                            text: "pixels"
                        }
                    }
                }
            }
        }
    }

    Button {
        text: "Stop"
        enabled: wigglerCoreIsRunning
        onClicked: {
            wigglerCoreIsRunning = false
            wiggleCore.stop()
        }
        x: 0
        y: parent.height - buttonAreaHeight
        width: parent.width * 0.5
        height: buttonAreaHeight
    }
    Button {
        text: "Start"
        enabled: !wigglerCoreIsRunning
        onClicked: {
            wigglerCoreIsRunning = true
            const wiggleData = getWiggleDataFromUI()
            wiggleCore.setWiggleData(wiggleData)
        }
        x: parent.width * 0.5
        y: parent.height - buttonAreaHeight
        width: parent.width * 0.5
        height: buttonAreaHeight
    }
}
