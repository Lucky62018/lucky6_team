var numOfSphere = 0;
var numOfRect = 0;
var numOfLight = 0;

var arr = new Array();

function initRectangle(t) {
    var r1_x=Number(document.getElementById("p1_x").value);
    var r1_y=Number(document.getElementById("p1_y").value);
    var r1_z=Number(document.getElementById("p1_z").value);
    var r2_x=Number(document.getElementById("p2_x").value);
    var r2_y=Number(document.getElementById("p2_y").value);
    var r2_z=Number(document.getElementById("p2_z").value);

    var geometry = new THREE.BoxGeometry( Math.abs(r1_x-r2_x), Math.abs(r1_y-r2_y), Math.abs(r1_z-r2_z) );
    var material = new THREE.MeshBasicMaterial( {color: 0x00ff00} );
    var rectangle = new THREE.Mesh( geometry, material );
    rectangle.position.set((r1_x+r2_x)/2, (r1_y+r2_y)/2, (r1_z+r2_z)/2);
    rectangle.name = numOfRect;

    scene.add( rectangle );

    var p1 = new Object();
    var p2 = new Object();
    p1.x = r1_x;
    p1.y = r1_y;
    p1.z = r1_z;
    p2.x = r2_x;
    p2.y = r2_y;
    p2.z = r2_z;
    var m = new Object();
    if(t=="marble") {
        m.type = "marble";
    }
    if(t=="metal") {
        m.type = "metal";
        var col = new Object();
        col.x = Number(document.getElementById("r_metal_x").value);
        col.y = Number(document.getElementById("r_metal_y").value);
        col.z = Number(document.getElementById("r_metal_z").value);
        m.color = col;
    }
    if(t=="glass") {
        m.type = "glass";
    }
    if(t=="pure") {
        m.type = "pureColor";
        var col = new Object();
        col.x = Number(document.getElementById("r_purecolor_x").value);
        col.y = Number(document.getElementById("r_purecolor_y").value);
        col.z = Number(document.getElementById("r_purecolor_z").value);
        m.color = col;
    }
    if(t=="checker") {
        m.type = "checker";
        var col1 = new Object();
        var col2 = new Object();
        col1.x = Number(document.getElementById("r_checker_x1").value);
        col1.y = Number(document.getElementById("r_checker_y1").value);
        col1.z = Number(document.getElementById("r_checker_z1").value);
        col2.x = Number(document.getElementById("r_checker_x2").value);
        col2.y = Number(document.getElementById("r_checker_y2").value);
        col2.z = Number(document.getElementById("r_checker_z2").value);
        m.color1 = col1;
        m.color2 = col2;
    }
    var obj = new Object();
    obj.type = "rectangle";
    obj.position1 = p1;
    obj.position2 = p2;
    obj.material = m;

    arr.push(obj);
}

function initSphere(t){
    var s_x=Number(document.getElementById("center_x").value);
    var s_y=Number(document.getElementById("center_y").value);
    var s_z=Number(document.getElementById("center_z").value);
    var r=Number(document.getElementById("sphere_radius").value);

    var geometry = new THREE.SphereGeometry( r, 32, 32 );
    var material = new THREE.MeshBasicMaterial( {color: 0xffff00} );
    var sphere = new THREE.Mesh( geometry, material );
    sphere.position.set(s_x,s_y,s_z);
    sphere.name = numOfSphere;
    
    scene.add( sphere );

    var center = new Object();
    center.x = s_x;
    center.y = s_y;
    center.z = s_z;
    var m = new Object();
    if(t=="marble") {
        m.type = "marble";
    }
    if(t=="metal") {
        m.type = "metal";
        var col = new Object();
        col.x = Number(document.getElementById("s_metal_x").value);
        col.y = Number(document.getElementById("s_metal_y").value);
        col.z = Number(document.getElementById("s_metal_z").value);
        m.color = col;
    }
    if(t=="glass") {
        m.type = "glass";
    }
    if(t=="pure") {
        m.type = "pureColor";
        var col = new Object();
        col.x = Number(document.getElementById("s_purecolor_x").value);
        col.y = Number(document.getElementById("s_purecolor_y").value);
        col.z = Number(document.getElementById("s_purecolor_z").value);
        m.color = col;
    }
    if(t=="checker") {
        m.type = "checker";
        var col1 = new Object();
        var col2 = new Object();
        col1.x = Number(document.getElementById("s_checker_x1").value);
        col1.y = Number(document.getElementById("s_checker_y1").value);
        col1.z = Number(document.getElementById("s_checker_z1").value);
        col2.x = Number(document.getElementById("s_checker_x2").value);
        col2.y = Number(document.getElementById("s_checker_y2").value);
        col2.z = Number(document.getElementById("s_checker_z2").value);
        m.color1 = col1;
        m.color2 = col2;
    }
    
    var obj = new Object();
    obj.type = "sphere";
    obj.radius = r;
    obj.center = center;
    obj.material = m;
    console.log(JSON.stringify(obj));
    arr.push(obj);
}


function initLight(){
    var s_x=Number(document.getElementById("light_x").value);
    var s_y=Number(document.getElementById("light_y").value);
    var s_z=Number(document.getElementById("light_z").value);
    var r=Number(document.getElementById("light_radius").value);

    var geometry = new THREE.SphereGeometry( r, 32, 32 );
    var material = new THREE.MeshBasicMaterial( {color: new THREE.Color(1,1,1).getHex()} );
    var light = new THREE.Mesh( geometry, material );
    light.position.set(s_x,s_y,s_z);
    light.name = numOfLight;
    
    scene.add( light );
    var c = new Object();
    c.x = s_x;
    c.y = s_y;
    c.z = s_z;
    var obj = new Object();
    obj.type = "light";
    obj.radius = r;
    obj.center = c;

    arr.push(obj);
}

function produce() {
    var img = new Object();
    img.x = Number(document.getElementById("image_x").value);
    img.y = Number(document.getElementById("image_y").value);
    img.definition = Number(document.getElementById("definition").value)

    var from = new Object();
    from.x = Number(document.getElementById("from_x").value);
    from.y = Number(document.getElementById("from_y").value);
    from.z = Number(document.getElementById("from_z").value);
    var at = new Object();
    at.x = Number(document.getElementById("at_x").value);
    at.y = Number(document.getElementById("at_y").value);
    at.z = Number(document.getElementById("at_z").value);
    var cam = new Object();
    cam.from = from;
    cam.at = at;
    cam.fieldOfView = Number(document.getElementById("fieldOfView").value);

    var obj = new Object();
    obj.image = img;
    obj.camera = cam;
    obj.objects = arr;
    console.log(JSON.stringify(obj));
    console.log("produce");
    $.ajax({
        type: 'POST',
        url: "http://localhost:8080",
        data: JSON.stringify(obj),
        contentType: 'application/json; charset=UTF-8',
        dataType: 'json', 
        success: function(data) {
            alert("success, please wait for the back-end generating the image")
        },
        error: function(xhr, type) {
            alert("error, request failed")
        }
    });
}

var renderer;
function initRender() {
    renderer = new THREE.WebGLRenderer({antialias:true});
    renderer.setSize(800, 800);
    document.getElementById("Preview").appendChild(renderer.domElement);
}

var camera;
function initCamera() {
    camera = new THREE.PerspectiveCamera();
    camera.position.set(0, 0, 200);
}

var scene;
function initScene() {
    scene = new THREE.Scene();
}

function initGround() {
    var geometry = new THREE.BoxGeometry( 100, 1, 100 );
    var material = new THREE.MeshBasicMaterial( { color: 0x404040 } );
    var ground = new THREE.Mesh( geometry, material );
    ground.position.set(0, -1, 0);

    scene.add( ground );
}

//用户交互插件 鼠标左键按住旋转，右键按住平移，滚轮缩放
var controls;
function initControls() {
    controls = new THREE.OrbitControls( camera, renderer.domElement );

    controls.enableDamping = true;  // 使动画循环使用时阻尼或自转 意思是否有惯性
    controls.enableZoom = true;  //是否可以缩放
    controls.autoRotate = false;  //是否自动旋转
    controls.minDistance  = 10;  //设置相机距离原点的最近距离
    controls.maxDistance  = 3000; //设置相机距离原点的最远距离
    controls.enablePan = true;   //是否开启右键拖拽
}

function render() {
    renderer.render( scene, camera );
}

function animate() {
    controls.update();  //更新控制器
    render();
    requestAnimationFrame(animate);
}

function initAxes() {
    var axesHelper = new THREE.AxesHelper( 50 );
    scene.add( axesHelper );
}

function draw() {
    initRender();
    initScene();
    initCamera();
    initControls();
    initGround();
    initAxes();

    animate();
}