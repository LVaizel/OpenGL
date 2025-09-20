#include "CustomMatrix.h"
static void Task1()
{
    float vectorInputs[3];

    cout << "Enter source location(x y z):";
    cin >> vectorInputs[0] >> vectorInputs[1] >> vectorInputs[2];
    glm::vec3 src = { vectorInputs[0], vectorInputs[1], vectorInputs[2] };//Vector for source

    cout << "Enter destination location(x y z):";
    cin >> vectorInputs[0] >> vectorInputs[1] >> vectorInputs[2];
    glm::vec3 dest = { vectorInputs[0], vectorInputs[1], vectorInputs[2] };//Vector for destinaton

    cout << "Enter speed per step:";
    float spd;//Scalar for speed
    cin >> spd;

    cout << "Steps required to reach is " << glm::distance(src, dest) / spd << endl;
}

static void Task2()
{
    float vectorInputs[3];

    cout << "Enter Point 1(x y z):";
    cin >> vectorInputs[0] >> vectorInputs[1] >> vectorInputs[2];
    glm::vec3 p1 = { vectorInputs[0], vectorInputs[1], vectorInputs[2] };//point1

    cout << "Enter point 2(x y z):";
    cin >> vectorInputs[0] >> vectorInputs[1] >> vectorInputs[2];
    glm::vec3 p2 = { vectorInputs[0], vectorInputs[1], vectorInputs[2] };//point2

    cout << "Enter point 3(x y z):";
    cin >> vectorInputs[0] >> vectorInputs[1] >> vectorInputs[2];
    glm::vec3 p3 = { vectorInputs[0], vectorInputs[1], vectorInputs[2] };//point3

    //Calculate lengths of sides

    float s1 = glm::distance(p1, p2);
    float s2 = glm::distance(p2, p3);
    float s3 = glm::distance(p3, p1);

    //Perimeter is sum of lengths of sides

    float perimeter = s1 + s2 + s3;

    //Since the magnitude of cross product of 2 vectors is equal to
    //the area of the parallelogram they represent
    //The area of the triangle is half of the paralleogram
    //p2-p1 is the vector of s1 and p3-p1 is the vector of side 2
    float area = glm::length(glm::cross(p2 - p1, p3 - p1)) / 2;

    cout << "Perimeter: " << perimeter << ", Area: " << area << endl;
}

static void Task3()
{
    glm::vec3 vertices[4];
    float vectorInputs[3];

    // Point 1
    cout << "Enter Point 1 (x y z): ";
    cin >> vectorInputs[0] >> vectorInputs[1] >> vectorInputs[2];
    vertices[0] = glm::vec3(vectorInputs[0], vectorInputs[1], vectorInputs[2]);

    // Point 2
    cout << "Enter Point 2 (x y z): ";
    cin >> vectorInputs[0] >> vectorInputs[1] >> vectorInputs[2];
    vertices[1] = glm::vec3(vectorInputs[0], vectorInputs[1], vectorInputs[2]);

    // Point 3
    cout << "Enter Point 3 (x y z): ";
    cin >> vectorInputs[0] >> vectorInputs[1] >> vectorInputs[2];
    vertices[2] = glm::vec3(vectorInputs[0], vectorInputs[1], vectorInputs[2]);

    // Point 4 = p1 + (p2 - p3)
    vertices[3] = vertices[0] + (vertices[2] - vertices[1]);

    // Depth
    float depth;
    cout << "Depth: ";
    cin >> depth;

    // Normal
    glm::vec3 normal = glm::normalize((glm::cross(vertices[0] - vertices[1], vertices[3] - vertices[1])));
    glm::vec3 depthVector = normal * depth;

    // Print cuboid vertices
    cout << "Cuboid Vertices:\n";
    for (int i = 0; i < 4; i++) {
        cout << "V" << i + 1 << ": " << glm::to_string(vertices[i]) << ", ";
    }
    cout << endl;

    for (int i = 0; i < 4; i++) {
        cout << "V" << i + 5 << ": " << glm::to_string(vertices[i] + depthVector);
        if (i != 3) cout << ", ";
    }
    cout << endl;
}

static void Task4()
{
    int dimInput[2];
    float valInput;
    cout << "Enter dims of Matrixes (x y):";
    cin >> dimInput[0] >> dimInput[1];
    CustomMatrix a(dimInput[0], dimInput[1]);
    for (int i = 0; i < dimInput[1]; i++)
    {
        for (int j = 0; j < dimInput[0]; j++)
        {
            cout << "Enter value at [" << i << "][" << j << "] for Matrix 1: ";
            cin >> valInput;
            a.SetVal(i, j, valInput);
        }
    }

    cout << "Enter dims of Matrix 2(x y):";
    cin >> dimInput[0] >> dimInput[1];
    CustomMatrix b(dimInput[0], dimInput[1]);


    for (int i = 0; i < dimInput[1]; i++)
    {
        for (int j = 0; j < dimInput[0]; j++)
        {
            cout << "Enter value at [" << i << "][" << j << "] for Matrix 1: ";
            cin >> valInput;
            b.SetVal(i, j, valInput);
        }
    }

    cout << "Matrix 1:" << endl;
    cout << a;
    cout << "Matrix 2:" << endl;
    cout << b;

    string add = (a + b).ToString();
    string sub = (a - b).ToString();
    string mult = (a * b).ToString();

    //If result is empty it means the operations cannot be performed
    if (add != "") { cout << "Matrix 1 + Matrix 2:" << endl << add; }
    else { cout << "Matrix 1 + Matrix 2: Cannot be performed due to dimension mismatch" << endl; }

    if (sub != "") { cout << "Matrix 1 - Matrix 2:" << endl << sub; }
    else { cout << "Matrix 1 - Matrix 2: Cannot be performed due to dimension mismatch" << endl; }

    if (mult != "") { cout << "Matrix 1 * Matrix 2:" << endl << mult; }
    else { cout << "Matrix 1 * Matrix 2: Cannot be performed due to dimension mismatch" << endl; }
}

static void Task4glm() {
    int dimInput[2];
    float valInput;

    cout << "Enter dims of GLM Matrix 1 (x y, max 4x4): ";
    cin >> dimInput[0] >> dimInput[1];

    if (dimInput[0] > 4 || dimInput[1] > 4) {
        cout << "GLM only supports up to 4x4 matrices.\n";
        return;
    }

    glm::mat4 a(0.0f), b(0.0f);

    for (int i = 0; i < dimInput[1]; i++) {
        for (int j = 0; j < dimInput[0]; j++) {
            cout << "Enter value at [" << i << "][" << j << "] for Matrix 1: ";
            cin >> valInput;
            a[j][i] = valInput;
        }
    }

    cout << "Enter dims of GLM Matrix 1 (x y, max 4x4): ";
    cin >> dimInput[0] >> dimInput[1];

    if (dimInput[0] > 4 || dimInput[1] > 4) {
        cout << "GLM only supports up to 4x4 matrices.\n";
        return;
    }

    cout << "Enter values for Matrix 2:" << endl;
    for (int i = 0; i < dimInput[1]; i++) {
        for (int j = 0; j < dimInput[0]; j++) {
            cout << "Enter value at [" << i << "][" << j << "] for Matrix 2: ";
            cin >> valInput;
            b[j][i] = valInput;
        }
    }

    cout << "GLM Matrix 1:" << endl << glm::to_string(a) << endl;
    cout << "GLM Matrix 2:" << endl << glm::to_string(b) << endl;

    glm::mat4 add = a + b;
    glm::mat4 sub = a - b;
    glm::mat4 mult = a * b;

    cout << "GLM Matrix 1 + Matrix 2:" << endl << glm::to_string(add) << endl;
    cout << "GLM Matrix 1 - Matrix 2:" << endl << glm::to_string(sub) << endl;
    cout << "GLM Matrix 1 * Matrix 2:" << endl << glm::to_string(mult) << endl;
}

int main()
{
	Task1();
	Task2();
	Task3();
	Task4();
	Task4glm();
    return 0;
}
