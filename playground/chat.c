#include <math.h>
#include <stdio.h>

typedef struct {
    float x, y, z;
} Vector3;

typedef struct {
    Vector3 origin;
    Vector3 direction;
} Ray;

typedef struct {
    Vector3 position;
    Vector3 look_at;
    Vector3 up;
    float fov;
    float aspect_ratio;
} Camera;

// Vector operations
Vector3 subtract(Vector3 a, Vector3 b) {
    return (Vector3){a.x - b.x, a.y - b.y, a.z - b.z};
}

Vector3 normalize(Vector3 v) {
    float l = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return (Vector3){v.x / l, v.y / l, v.z / l};
}

Vector3 cross(Vector3 a, Vector3 b) {
    return (Vector3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

float dot(Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Camera initialization
void init_camera(Camera *camera, Vector3 position, Vector3 look_at, Vector3 up, float fov, float aspect_ratio) {
    camera->position = position;
    camera->look_at = look_at;
    camera->up = up;
    camera->fov = fov;
    camera->aspect_ratio = aspect_ratio;
}

// Generate a ray from the camera through a pixel
Ray generate_ray(Camera *camera, float u, float v) {
    Vector3 w = normalize(subtract(camera->position, camera->look_at));
    Vector3 u_vec = normalize(cross(camera->up, w));
    Vector3 v_vec = cross(w, u_vec);

    float half_width = tan(camera->fov / 2);
    float half_height = half_width / camera->aspect_ratio;

    Vector3 direction = normalize(
        (Vector3){
            w.x + u * half_width * u_vec.x + v * half_height * v_vec.x,
            w.y + u * half_width * u_vec.y + v * half_height * v_vec.y,
            w.z + u * half_width * u_vec.z + v * half_height * v_vec.z
        }
    );

    return (Ray){camera->position, direction};
}

int main() {
    // Example usage
    Camera camera;
    init_camera(&camera, (Vector3){0, 0, 5}, (Vector3){0, 0, 0}, (Vector3){0, 1, 0}, M_PI / 3, 16.0 / 9.0);

    // Generate a ray through the center of the screen
    Ray ray = generate_ray(&camera, 0.5, 0.5);

    printf("Ray origin: (%f, %f, %f)\n", ray.origin.x, ray.origin.y, ray.origin.z);
    printf("Ray direction: (%f, %f, %f)\n", ray.direction.x, ray.direction.y, ray.direction.z);

    return 0;
}
