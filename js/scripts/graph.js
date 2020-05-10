$("#fileImport").click(function () {
    $("#files").click();
})

var renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight );
document.body.appendChild( renderer.domElement );

var camera = new THREE.PerspectiveCamera( 45, window.innerWidth / window.innerHeight, 1, 500 );
camera.position.set(0, 0, 100);
camera.lookAt(0, 0, 0);

var scene = new THREE.Scene();

//create a blue LineBasicMaterial
var material = new THREE.LineBasicMaterial( { color: 0x0000ff } );

function drawConnectedLine(p1, p2) {
    points = [];
    points.push( new THREE.Vector3( p1["pos"][0], p1["pos"][1], p1["pos"][2] ) );
    points.push( new THREE.Vector3( p2["pos"][0], p2["pos"][1], p2["pos"][2] ) );
    geometry = new THREE.BufferGeometry().setFromPoints( points );
    line = new THREE.Line( geometry, material );
    scene.add( line );
}

function drawLine(line) {
    drawConnectedLine(line["start_point"], line["end_point"]);
}

function drawPolygon(polygon) {
    var i = 0;
    var n = polygon["point"].length;
    for (i = 1; i < n; i++) {
        drawConnectedLine(polygon["point"][i-1], polygon["point"][i]);
    }
    if (n > 0) {
        drawConnectedLine(polygon["point"][n - 1], polygon["point"][0]);
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
        decodedMessage["line"].forEach(drawPolygon)
        decodedMessage["polygon"].forEach(drawPolygon)

        renderer.render( scene, camera );
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
