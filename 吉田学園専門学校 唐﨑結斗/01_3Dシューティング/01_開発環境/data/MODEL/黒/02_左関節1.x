xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 34;
 -1.33949;0.00139;-0.51606;,
 -2.39781;0.00139;-0.89732;,
 -2.39781;-0.91241;0.01648;,
 -1.33949;-0.53115;0.01648;,
 -2.39781;0.00139;0.93028;,
 -1.33949;0.00139;0.54902;,
 -2.39781;0.91519;0.01648;,
 -1.33949;0.53393;0.01648;,
 -2.39781;0.00139;-0.89732;,
 -1.33949;0.00139;-0.51606;,
 -3.48852;0.00139;-1.34078;,
 -3.48852;-1.35587;0.01648;,
 -3.48852;0.00139;1.37374;,
 -3.48852;1.35865;0.01648;,
 -3.48852;0.00139;-1.34078;,
 -4.76505;0.00139;-0.88836;,
 -4.76505;-0.90345;0.01648;,
 -4.76505;0.00139;0.92132;,
 -4.76505;0.90623;0.01648;,
 -4.76505;0.00139;-0.88836;,
 -6.04159;0.00139;-0.43594;,
 -6.04158;-0.45103;0.01648;,
 -6.04159;0.00139;0.46890;,
 -6.04158;0.45381;0.01648;,
 -6.04159;0.00139;-0.43594;,
 -7.31812;0.00139;0.01648;,
 -7.31812;0.00139;0.01648;,
 -7.31812;0.00139;0.01648;,
 -7.31812;0.00139;0.01648;,
 -0.01146;0.00139;0.01648;,
 -1.33949;0.00139;-0.51606;,
 -1.33949;-0.53115;0.01648;,
 -1.33949;0.00139;0.54902;,
 -1.33949;0.53393;0.01648;;
 
 24;
 4;3,2,1,0;,
 4;5,4,2,3;,
 4;7,6,4,5;,
 4;9,8,6,7;,
 4;2,11,10,1;,
 4;4,12,11,2;,
 4;6,13,12,4;,
 4;8,14,13,6;,
 4;11,16,15,10;,
 4;12,17,16,11;,
 4;13,18,17,12;,
 4;14,19,18,13;,
 4;16,21,20,15;,
 4;17,22,21,16;,
 4;18,23,22,17;,
 4;19,24,23,18;,
 3;21,25,20;,
 3;22,26,21;,
 3;23,27,22;,
 3;24,28,23;,
 3;31,30,29;,
 3;32,31,29;,
 3;33,32,29;,
 3;30,33,29;;
 
 MeshMaterialList {
  3;
  24;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.194510;0.194510;0.194510;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.160000;0.160000;0.160000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  28;
  0.259847;-0.682818;-0.682818;,
  0.259847;-0.682818;0.682818;,
  0.259847;0.682818;0.682818;,
  0.261608;-0.682481;-0.682481;,
  0.261608;-0.682481;0.682481;,
  0.261608;0.682481;0.682481;,
  0.017196;-0.707002;-0.707002;,
  0.017196;-0.707002;0.707002;,
  0.017196;0.707002;0.707002;,
  -0.243091;-0.685897;-0.685895;,
  -0.243091;-0.685897;0.685896;,
  -0.243091;0.685897;0.685896;,
  -0.243090;-0.685898;-0.685894;,
  -0.243090;-0.685898;0.685894;,
  -0.243090;0.685898;0.685894;,
  -0.243090;-0.685899;-0.685894;,
  0.272795;-0.680288;-0.680288;,
  0.259847;0.682818;-0.682818;,
  0.261608;0.682481;-0.682481;,
  0.017196;0.707002;-0.707002;,
  -0.243091;0.685897;-0.685896;,
  -0.243090;0.685898;-0.685894;,
  -0.243090;-0.685899;0.685894;,
  -0.243090;0.685899;0.685894;,
  -0.243090;0.685899;-0.685894;,
  0.272795;-0.680288;0.680288;,
  0.272795;0.680288;0.680288;,
  0.272795;0.680288;-0.680288;;
  24;
  4;0,3,3,0;,
  4;1,4,4,1;,
  4;2,5,5,2;,
  4;17,18,18,17;,
  4;3,6,6,3;,
  4;4,7,7,4;,
  4;5,8,8,5;,
  4;18,19,19,18;,
  4;6,9,9,6;,
  4;7,10,10,7;,
  4;8,11,11,8;,
  4;19,20,20,19;,
  4;9,12,12,9;,
  4;10,13,13,10;,
  4;11,14,14,11;,
  4;20,21,21,20;,
  3;12,15,12;,
  3;13,22,13;,
  3;14,23,14;,
  3;21,24,21;,
  3;0,0,16;,
  3;1,1,25;,
  3;2,2,26;,
  3;17,17,27;;
 }
 MeshTextureCoords {
  34;
  0.000000;1.000000;,
  0.000000;0.800000;,
  0.250000;0.800000;,
  0.250000;1.000000;,
  0.500000;0.800000;,
  0.500000;1.000000;,
  0.750000;0.800000;,
  0.750000;1.000000;,
  1.000000;0.800000;,
  1.000000;1.000000;,
  0.000000;0.600000;,
  0.250000;0.600000;,
  0.500000;0.600000;,
  0.750000;0.600000;,
  1.000000;0.600000;,
  0.000000;0.400000;,
  0.250000;0.400000;,
  0.500000;0.400000;,
  0.750000;0.400000;,
  1.000000;0.400000;,
  0.000000;0.200000;,
  0.250000;0.200000;,
  0.500000;0.200000;,
  0.750000;0.200000;,
  1.000000;0.200000;,
  0.125000;0.000000;,
  0.250000;0.000000;,
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
