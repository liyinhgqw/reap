$("#fileImport").click(function () {
    $("#files").click();
})

var elem = document.getElementById('draw-shapes');
var params = { width: 800, height: 600, type:Two.Types.svg };
var two = new Two(params).appendTo(elem);

var scale = 1
var min_x = 1000000, max_x = 0, min_y = 1000000, max_y = 0;
var default_stroke = "rgba(255, 0, 0, 0.5)"

function drawConnectedLine(p1, p2, stroke) {
    var line = two.makeLine(p1["pos"][0] - min_x, params.height - (p1["pos"][1] - min_y),
        p2["pos"][0] - min_x, params.height - (p2["pos"][1] - min_y));
    line.linewidth = 3;
    line.stroke = stroke;
    console.log(p1, p2);
    two.update();
}

function drawLine(line) {
    console.log(line);
    drawConnectedLine(line["startPoint"], line["endPoint"], "rgba(0, 0, 255, 0.5)");
}

function drawPolygon(polygon) {
    var i;
    var n = polygon["point"].length;
    for (i = 1; i < n; i++) {
        drawConnectedLine(polygon["point"][i-1], polygon["point"][i], default_stroke);
    }
    if (n > 0) {
        drawConnectedLine(polygon["point"][n - 1], polygon["point"][0], default_stroke);
    }
}

function normalize(graph) {
    for (var plg of graph["polygon"]) {
        for (var p of plg["point"]) {
            min_x = Math.min(min_x, p["pos"][0]);
            max_x = Math.max(max_x, p["pos"][0]);
            min_y = Math.min(min_y, p["pos"][1]);
            max_y = Math.max(max_y, p["pos"][1]);
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
        decodedMessage["line"].forEach(drawLine);
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
