var numOfSphere = 0;
var numOfRect = 0;
var numOfLight = 0;

function initRectangle() {
    var r1_x=document.getElementById("p1_x").value;
    var r1_y=document.getElementById("p1_y").value;
    var r1_z=document.getElementById("p1_z").value;
    var r2_x=document.getElementById("p2_x").value;
    var r2_y=document.getElementById("p2_y").value;
    var r2_z=document.getElementById("p2_z").value;

    var geometry = new THREE.BoxGeometry( Math.abs(r1_x-r2_x), Math.abs(r1_y-r2_y), Math.abs(r1_z-r2_z) );
    var material = new THREE.MeshBasicMaterial( {color: 0x00ff00} );
    var rectangle = new THREE.Mesh( geometry, material );
    rectangle.position.set((r1_x+r2_x)/2, (r1_y+r2_y)/2, (r1_z+r2_z)/2);
    rectangle.name = numOfRect;

    scene.add( rectangle );
}

function initSphere(){
    var s_x=document.getElementById("center_x").value;
    var s_y=document.getElementById("center_y").value;
    var s_z=document.getElementById("center_z").value;
    var r=document.getElementById("sphere_radius").value;

    var geometry = new THREE.SphereGeometry( r, 32, 32 );
    var material = new THREE.MeshBasicMaterial( {color: 0xffff00} );
    var sphere = new THREE.Mesh( geometry, material );
    sphere.position.set(s_x,s_y,s_z);
    sphere.name = numOfSphere;
    
    scene.add( sphere );
}


function initLight(){
    var s_x=document.getElementById("light_x").value;
    var s_y=document.getElementById("light_y").value;
    var s_z=document.getElementById("light_z").value;
    var r=document.getElementById("light_radius").value;

    var geometry = new THREE.SphereGeometry( r, 32, 32 );
    var material = new THREE.MeshBasicMaterial( {color: new THREE.Color(1,1,1).getHex()} );
    var light = new THREE.Mesh( geometry, material );
    light.position.set(s_x,s_y,s_z);
    light.name = numOfLight;
    
    scene.add( light );
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