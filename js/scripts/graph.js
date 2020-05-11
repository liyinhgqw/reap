$("#fileImport").click(function () {
    $("#files").click();
})

var elem = document.getElementById('draw-shapes');
var params = { width: 800, height: 600, type:Two.Types.svg };
var two = new Two(params).appendTo(elem);

var scale = 1

function drawConnectedLine(p1, p2) {
    var line = two.makeLine(p1["pos"][0], p1["pos"][1], p2["pos"][0], p2["pos"][1]);
    line.linewidth = 3;
    line.stroke = "rgba(255, 0, 0, 0.5)";
    console.log(p1, p2);
    two.update();
}

function drawLine(line) {
    drawConnectedLine(line["start_point"], line["end_point"]);
}

function drawPolygon(polygon) {
    var i;
    var n = polygon["point"].length;
    for (i = 1; i < n; i++) {
        drawConnectedLine(polygon["point"][i-1], polygon["point"][i]);
    }
    if (n > 0) {
        drawConnectedLine(polygon["point"][n - 1], polygon["point"][0]);
    }
}

function normalize(graph) {
    var min_x = 1000000, max_x = 0, min_y = 1000000, max_y = 0;
    for (var plg of graph["polygon"]) {
        for (var p of plg["point"]) {
            min_x = Math.min(min_x, p["pos"][0]);
            max_x = Math.max(max_x, p["pos"][0]);
            min_y = Math.min(min_y, p["pos"][1]);
            max_y = Math.max(max_y, p["pos"][1]);
        }
    }
    var cx = (min_x + max_x) * 0.5;
    var cy = (min_y + max_y) * 0.5;

    console.log(cx);
    console.log(cy);

    for (var plg of graph["polygon"]) {
        for (var p of plg["point"]) {
            p["pos"][0] = p["pos"][0] - min_x;
            p["pos"][1] = p["pos"][1] - min_y;
        }
    }
}

function decodeMessage(buffer) {
    protobuf.load("../reap/proto/geometry.proto", function(err, root) {
        if (err)
            throw err;

        // Obtain a message type
        var graphMessage = root.lookupType("reap.Graph");
        var decodedMessage = graphMessage.decode( new Uint8Array(buffer));

        console.log(decodedMessage);
        normalize(decodedMessage);
        decodedMessage["line"].forEach(drawPolygon);
        decodedMessage["polygon"].forEach(drawPolygon);

        two.update();
        two.play();
    });
}

function fileImport() {
    var reader = new FileReader();
    var file = document.getElementById('files').files[0];
    reader.onload = function(e) {
        var arrayBuffer = reader.result;
        decodeMessage(arrayBuffer)
    }

    reader.readAsArrayBuffer(file);
}
