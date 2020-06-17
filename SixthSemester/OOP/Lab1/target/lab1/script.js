let camera, renderer, scene, wSocket, connected, core;
let vertex = [];
let vertexMaterials = [];
let lineS = [], lineE = [];
let materialLines = [];

init();
animate();

function connect() {
    wSocket = new WebSocket("ws://localhost:8080/action");
    wSocket.onmessage = onMessage;
    connected = true;
}

function add(div, text) {
    const x = document.getElementById(div);
    const option = document.createElement("option");
    option.text = text;
    x.add(option);
}

function onMessage(event) {
    const json = JSON.parse(event.data);
    console.log(json);
    if (json.command === "graph") {
        let countVertex = json.countVertex;
        for (let i = 0; i < countVertex; i++) {
            let x = json["vertex" + i + 'X'];
            let y = json["vertex" + i + 'Y'];
            let z = json["vertex" + i + 'Z'];
            add("point1", i);
            add("point2", i);
            vertex.push(new THREE.Vector3(x, y, z));
            createSphere(x, y, z);


        }
        let countLine = json.countLine;
        for (let i = 0; i < countLine; i++) {
            let s = json["line" + i + 's'];
            let e = json["line" + i + 'e'];
            lineS.push(s);
            lineE.push(e);
            createLine(s, e);
        }
    } else if (json.command === "path") {
        setDefColors();
        let countVertex = json.count;
        let vertexes = [];
        for (let i = 0; i < countVertex; i++) {
            let s = json["vertex" + i];
            vertexes.push(s);
        }
        changeColor(vertexes);
    }
}

function changeColor(vertexes) {
    for (let i = 0; i < vertexes.length; i++) {
        vertexMaterials[vertexes[i]].color.set(0xff1010);
    }

    for (let i = 0; i < lineS.length; i++) {
        for (let j = 0; j < vertexes.length - 1; j++) {
            if (vertexes[j] === lineS[i] && vertexes[j + 1] === lineE[i] ||
                vertexes[j] === lineE[i] && vertexes[j + 1] === lineS[i]) {
                materialLines[i].color.set(0xff0000);
            }

        }
    }
}

function setDefColors() {
    for (let i = 0; i < vertexMaterials.length; i++) {
        vertexMaterials[i].color.set(0x20296d);
    }

    for (let i = 0; i < materialLines.length; i++) {
        materialLines[i].color.set(0x0000ff);
    }
}

function start() {
    if (!connected || wSocket.closed) {
        connect();
    }

    const obj = {
        command: "search",
        "start": document.getElementById("point1").selectedIndex,
        "end": document.getElementById("point2").selectedIndex,
    };
    const msg = JSON.stringify(obj);
    console.log(obj);
    sendMessage(msg);
}


window.addEventListener("keypress", manageKey, false);

function manageKey(e) {
    if (e.keyCode === 32) {
        start();
    }
}

function sendMessage(msg) {
    waitForSocketConnection(wSocket, function () {
        wSocket.send(msg);
    });
}


function waitForSocketConnection(socket, callback) {
    setTimeout(
        function () {
            if (socket.readyState === 1) {
                console.log("Connection is made");
                if (callback != null) {
                    callback();
                }

            } else {
                console.log("wait for connection...");
                waitForSocketConnection(socket, callback);
            }
        }, 5); // wait 5 milisecond for the connection
}


function init() {
    if (!connected || wSocket.closed) {
        connect();
    }
    const divForImage = document.getElementById("image");
    scene = new THREE.Scene();
    camera = new THREE.PerspectiveCamera(70, window.innerWidth / window.innerHeight, 1, 10000);
    camera.position.set(300, 300, 300);
    scene.add(camera);

    const light = new THREE.SpotLight(0xffffff, 1.5);
    light.position.set(300, 300, 300);
    scene.add(light);

    const helper = new THREE.GridHelper(3000, 300);
    helper.position.y = 0;
    helper.material.opacity = 0.25;
    helper.material.transparent = true;
    scene.add(helper);

    renderer = new THREE.WebGLRenderer({antialias: true});
    renderer.setClearColor(new THREE.Color('white'));
    renderer.setPixelRatio(window.devicePixelRatio);
    renderer.setSize(window.innerWidth, window.innerHeight - document.getElementById("info").offsetHeight);
    divForImage.appendChild(renderer.domElement);

    new THREE.OrbitControls(camera, renderer.domElement);
    new THREE.TransformControls(camera, renderer.domElement);

}

function createSphere(x, y, z) {
    const sphereGeometry = new THREE.SphereGeometry(5, 50, 50, 0, Math.PI * 2, 0, Math.PI * 2);
    const mat = new THREE.MeshStandardMaterial({color: "#20296d"});
    vertexMaterials.push(mat);
    core = new THREE.Mesh(sphereGeometry, mat);
    core.position.x = x;
    core.position.y = y;
    core.position.z = z;
    scene.add(core);
    sphereGeometry.dynamic = true;
}

function createLine(s, e) {
    const material = new THREE.LineBasicMaterial({color: 0x0000ff});

    const geometry = new THREE.Geometry();
    geometry.vertices.push(vertex[s], vertex[e]);
    materialLines.push(material);
    const line = new THREE.Line(geometry, material);
    scene.add(line);
    line.dynamic = true;
}

function animate() {
    requestAnimationFrame(animate);
    render();
}

function render() {
    renderer.render(scene, camera);
}
