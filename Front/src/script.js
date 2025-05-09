const scene = document.getElementById('scene');
const size = 40;

const matriz = [
    [
      ["#ff0000", "#00ff00", null],
      [null, "#0000ff", null],
      [null, "#ffff00", "#ff00ff"]
    ],
    [
      [null, "#00ffff", "#ffffff"],
      ["#888888", "#444444", null],
      [null, null, "#222222"]
    ],
    [
      ["orange", null, null],
      ["pink", "lime", "cyan"],
      [null, "brown", null]
    ]
  ];

for (let z = 0; z < matriz.length; z++) {
    for (let y = 0; y < matriz[z].length; y++) {
        for (let x = 0; x < matriz[z][y].length; x++) {
            const color = matriz[z][y][x];
            if (color) {
            const cube = document.createElement('div');
            cube.className = 'cube';
            cube.style.transform = `translate3d(${x * size}px, ${y * size}px, ${z * size}px)`;

            ['front', 'back', 'right', 'left', 'top', 'bottom'].forEach(face => {
                const faceDiv = document.createElement('div');
                faceDiv.className = `face ${face}`;
                faceDiv.style.background = color;
                cube.appendChild(faceDiv);
            });

            scene.appendChild(cube);
            }
        }
    }
}

// Rotação da câmera com mouse
let isDragging = false;
let startX = 0, startY = 0;
let rotX = -30, rotY = 45;

function updateRotation() {
    scene.style.transform = `rotateX(${rotX}deg) rotateY(${rotY}deg)`;
}

document.addEventListener('mousedown', (e) => {
    isDragging = true;
    startX = e.clientX;
    startY = e.clientY;
});

document.addEventListener('mousemove', (e) => {
    if (!isDragging) return;
    const dx = e.clientX - startX;
    const dy = e.clientY - startY;
    rotY += dx * 0.3;
    rotX -= dy * 0.3;
    rotX = Math.max(-89, Math.min(89, rotX)); // limita o giro vertical
    updateRotation();
    startX = e.clientX;
    startY = e.clientY;
});

document.addEventListener('mouseup', () => {
    isDragging = false;
});

document.addEventListener('mouseleave', () => {
    isDragging = false;
});