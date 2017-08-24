// MatrixStuff.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/constants.hpp> // glm::pi

#define GLM_ENABLE_EXPERIMENTAL true

#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

union Mat4f
{
    // Column Major
    struct
    {
        float m00, m10, m20, m30,
              m01, m11, m21, m31,
              m02, m12, m22, m32,
              m03, m13, m23, m33;
    };
    float m[16];
};

Mat4f mult(Mat4f & A, Mat4f B)
{
    Mat4f result;

    result.m[0] = A.m[0] * B.m[0] + A.m[1] * B.m[4] + A.m[2] * B.m[8] + A.m[3] * B.m[12];
    result.m[1] = A.m[0] * B.m[1] + A.m[1] * B.m[5] + A.m[2] * B.m[9] + A.m[3] * B.m[13];
    result.m[2] = A.m[0] * B.m[2] + A.m[1] * B.m[6] + A.m[2] * B.m[10] + A.m[3] * B.m[14];
    result.m[3] = A.m[0] * B.m[3] + A.m[1] * B.m[7] + A.m[2] * B.m[11] + A.m[3] * B.m[15];

    result.m[4] = A.m[4] * B.m[0] + A.m[5] * B.m[4] + A.m[6] * B.m[8] + A.m[7] * B.m[12];
    result.m[5] = A.m[4] * B.m[1] + A.m[5] * B.m[5] + A.m[6] * B.m[9] + A.m[7] * B.m[13];
    result.m[6] = A.m[4] * B.m[2] + A.m[5] * B.m[6] + A.m[6] * B.m[10] + A.m[7] * B.m[14];
    result.m[7] = A.m[4] * B.m[3] + A.m[5] * B.m[7] + A.m[6] * B.m[11] + A.m[7] * B.m[15];

    result.m[8] = A.m[8] * B.m[0] + A.m[9] * B.m[4] + A.m[10] * B.m[8] + A.m[11] * B.m[12];
    result.m[9] = A.m[8] * B.m[1] + A.m[9] * B.m[5] + A.m[10] * B.m[9] + A.m[11] * B.m[13];
    result.m[10] = A.m[8] * B.m[2] + A.m[9] * B.m[6] + A.m[10] * B.m[10] + A.m[11] * B.m[14];
    result.m[11] = A.m[8] * B.m[3] + A.m[9] * B.m[7] + A.m[10] * B.m[11] + A.m[11] * B.m[15];

    result.m[12] = A.m[12] * B.m[0] + A.m[13] * B.m[4] + A.m[14] * B.m[8] + A.m[15] * B.m[12];
    result.m[13] = A.m[12] * B.m[1] + A.m[13] * B.m[5] + A.m[14] * B.m[9] + A.m[15] * B.m[13];
    result.m[14] = A.m[12] * B.m[2] + A.m[13] * B.m[6] + A.m[14] * B.m[10] + A.m[15] * B.m[14];
    result.m[15] = A.m[12] * B.m[3] + A.m[13] * B.m[7] + A.m[14] * B.m[11] + A.m[15] * B.m[15];

    return result;
}

void populate(glm::mat4& src, Mat4f& dest)
{
#if defined(USE_MATRIX_ACCESSOR)
    dest.m00 = src[0][0];
    dest.m01 = src[0][1];
    dest.m02 = src[0][2];
    dest.m03 = src[0][3];
    dest.m10 = src[1][0];
    dest.m11 = src[1][1];
    dest.m12 = src[1][2];
    dest.m13 = src[1][3];
    dest.m20 = src[2][0];
    dest.m21 = src[2][1];
    dest.m22 = src[2][2];
    dest.m23 = src[2][3];
    dest.m30 = src[3][0];
    dest.m31 = src[3][1];
    dest.m32 = src[3][2];
    dest.m33 = src[3][3];
#else
    dest.m[0]  = src[0][0];
    dest.m[4]  = src[0][1];
    dest.m[8]  = src[0][2];
    dest.m[12] = src[0][3];
    dest.m[1]  = src[1][0];
    dest.m[5]  = src[1][1];
    dest.m[9]  = src[1][2];
    dest.m[13] = src[1][3];
    dest.m[2]  = src[2][0];
    dest.m[6]  = src[2][1];
    dest.m[10] = src[2][2];
    dest.m[14] = src[2][3];
    dest.m[3]  = src[3][0];
    dest.m[7]  = src[3][1];
    dest.m[11] = src[3][2];
    dest.m[15] = src[3][3];
#endif
}

void debugMat4f(Mat4f& src)
{
    printf(" %f %f %f %f\n", src.m[0], src.m[4], src.m[8], src.m[12]);
    printf(" %f %f %f %f\n", src.m[1], src.m[5], src.m[9], src.m[13]);
    printf(" %f %f %f %f\n", src.m[2], src.m[6], src.m[10], src.m[14]);
    printf(" %f %f %f %f\n", src.m[3], src.m[7], src.m[11], src.m[15]);
}

int main()
{
    glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
    glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));

    glm::mat4 PV = Projection * View;

    Mat4f myProj;
    Mat4f myView;
    populate(Projection, myProj);
    populate(View, myView);

    Mat4f myPV = mult(myProj, myView);

    printf("Projection Matrix --------------------------\n");
    printf("%s\n", glm::to_string(Projection).c_str());
    debugMat4f(myProj);

    printf("View Matrix --------------------------------\n");
    printf("%s\n", glm::to_string(View).c_str());
    debugMat4f(myView);

    printf("PV matrix ----------------------------------\n");
    printf("%s\n", glm::to_string(PV).c_str());
    debugMat4f(myPV);

    scanf_s("-");
    return 0;
}

