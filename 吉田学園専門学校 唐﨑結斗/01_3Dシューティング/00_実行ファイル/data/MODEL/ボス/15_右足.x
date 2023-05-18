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
 288;
 4.64721;-1.66962;5.68741;,
 3.09313;-1.66962;6.93739;,
 3.41917;-2.92725;9.39883;,
 5.13626;-2.92725;6.41820;,
 1.53906;-1.66962;7.87463;,
 1.70208;-2.92725;10.43438;,
 -0.01501;-1.66962;7.87463;,
 -0.01501;-2.92725;10.43437;,
 -1.56907;-1.66962;7.87463;,
 -1.73209;-2.92725;10.43438;,
 -3.12315;-1.66962;6.93738;,
 -3.12314;-3.08318;8.38506;,
 -4.67722;-1.66962;5.68741;,
 -4.67722;-3.08318;6.73063;,
 3.76052;-4.36114;10.41934;,
 5.64829;-4.36114;8.59138;,
 1.87276;-4.36114;11.45490;,
 -0.01500;-4.36114;11.45490;,
 -1.90277;-4.36114;11.45489;,
 -3.79053;-4.36114;10.41935;,
 -5.67829;-4.36114;8.59137;,
 4.03357;-5.93148;11.32133;,
 6.05786;-5.93148;9.49338;,
 2.00928;-5.93148;12.35690;,
 -0.01501;-5.93148;12.35690;,
 -2.03929;-5.93148;12.35690;,
 -4.06358;-5.93148;11.32133;,
 -6.08787;-5.93148;9.49338;,
 4.61718;-6.68699;12.31668;,
 6.93327;-6.68699;10.93559;,
 2.30109;-6.68699;13.35223;,
 -0.01501;-6.68699;13.35223;,
 -2.33110;-6.68699;13.35224;,
 -4.64719;-6.68699;12.31668;,
 -6.96328;-6.68699;10.93559;,
 4.61718;-7.34605;12.31668;,
 6.93327;-7.34605;10.93559;,
 2.30109;-7.34605;13.35223;,
 -0.01501;-7.34605;13.35223;,
 -2.33110;-7.34605;13.35224;,
 -4.64719;-7.34605;12.31668;,
 -6.96328;-7.34605;10.93559;,
 4.61718;-8.00506;12.31668;,
 6.93327;-8.00506;10.93559;,
 2.30109;-8.00506;13.35223;,
 -0.01501;-8.00506;13.35223;,
 -2.33110;-8.00506;13.35224;,
 -4.64719;-8.00506;12.31668;,
 -6.96328;-8.00506;10.93559;,
 -4.67722;-1.66962;5.68741;,
 -4.74750;-1.66962;5.13733;,
 -6.05766;-3.08318;3.01143;,
 -4.67722;-3.08318;6.73063;,
 -6.05765;-1.66962;2.55263;,
 -6.59234;-3.08318;0.42675;,
 -6.59234;-1.66962;-0.03206;,
 -6.59234;-3.08318;-2.15795;,
 -6.59234;-1.66962;-2.61676;,
 -6.05765;-3.08318;-4.74265;,
 -6.05765;-1.66962;-5.20145;,
 -6.69150;-2.92725;-7.96173;,
 -6.05765;-1.66962;-7.78615;,
 -5.16627;-2.92725;-11.48171;,
 -7.35514;-4.36114;4.05501;,
 -5.67829;-4.36114;8.59137;,
 -8.00463;-4.36114;-1.66405;,
 -7.35514;-4.36114;-4.80373;,
 -7.35514;-4.36114;-7.94341;,
 -5.67830;-4.36114;-11.72566;,
 -5.67830;-4.36114;-14.61009;,
 -7.88598;-5.93148;4.62300;,
 -6.08787;-5.93148;9.49338;,
 -8.58245;-5.93148;-1.50966;,
 -7.88598;-5.93148;-7.46575;,
 -6.08787;-5.93148;-11.49542;,
 -6.08787;-5.93148;-14.58849;,
 -6.08787;-5.93148;-17.68154;,
 -9.02059;-6.68699;5.30834;,
 -6.96328;-6.68699;10.93559;,
 -9.81745;-6.68699;-1.70834;,
 -9.02059;-6.68699;-8.52301;,
 -6.96328;-6.68699;-12.91260;,
 -6.96328;-6.68699;-16.45155;,
 -6.96328;-6.68699;-19.99046;,
 -9.02059;-7.34605;5.30834;,
 -6.96328;-7.34605;10.93559;,
 -9.81745;-7.34605;-1.70834;,
 -9.02059;-7.34605;-8.52301;,
 -6.96328;-7.34605;-12.91260;,
 -6.96328;-7.34605;-16.45155;,
 -6.96328;-7.34605;-19.99046;,
 -9.02059;-8.00506;5.30834;,
 -6.96328;-8.00506;10.93559;,
 -9.81745;-8.00506;-1.70834;,
 -9.02059;-8.00506;-8.52301;,
 -6.96328;-8.00506;-12.91260;,
 -6.96328;-8.00506;-16.45155;,
 -6.96328;-8.00506;-19.99046;,
 -6.05765;-1.66962;-7.78615;,
 -3.12315;-1.66962;-10.94388;,
 -3.44918;-2.92725;-14.11558;,
 -5.16627;-2.92725;-11.48171;,
 -2.02922;-1.66962;-7.78615;,
 -1.73209;-2.92725;-11.48171;,
 -0.01501;-1.66962;-10.94388;,
 -0.01501;-2.92725;-14.11558;,
 1.99921;-1.66962;-7.78615;,
 1.70208;-2.92725;-11.48171;,
 3.09313;-1.66962;-10.94389;,
 3.41917;-2.92725;-14.11558;,
 6.02764;-1.66962;-7.78615;,
 5.13626;-2.92725;-11.48171;,
 -3.79053;-4.36114;-17.50578;,
 -5.67830;-4.36114;-14.61009;,
 -1.90277;-4.36114;-14.61009;,
 -0.01501;-4.36114;-17.50578;,
 1.87276;-4.36114;-14.61009;,
 3.76052;-4.36114;-17.50578;,
 5.64829;-4.36114;-14.61009;,
 -4.06358;-5.93148;-20.78662;,
 -6.08787;-5.93148;-17.68154;,
 -2.03930;-5.93148;-17.68154;,
 -0.01501;-5.93148;-20.78663;,
 2.00929;-5.93148;-17.68154;,
 4.03357;-5.93148;-20.78662;,
 6.05786;-5.93148;-17.68154;,
 -4.64719;-6.68699;-23.54316;,
 -6.96328;-6.68699;-19.99046;,
 -2.33110;-6.68699;-19.99046;,
 -0.01501;-6.68699;-23.54316;,
 2.30109;-6.68699;-19.99046;,
 4.61718;-6.68699;-23.54315;,
 6.93327;-6.68699;-19.99046;,
 -4.64719;-7.34605;-23.54316;,
 -6.96328;-7.34605;-19.99046;,
 -2.33110;-7.34605;-19.99046;,
 -0.01501;-7.34605;-23.54316;,
 2.30109;-7.34605;-19.99046;,
 4.61718;-7.34605;-23.54315;,
 6.93327;-7.34605;-19.99046;,
 -4.64719;-8.00506;-23.54316;,
 -6.96328;-8.00506;-19.99046;,
 -2.33110;-8.00506;-19.99046;,
 -0.01501;-8.00506;-23.54316;,
 2.30109;-8.00506;-19.99046;,
 4.61718;-8.00506;-23.54315;,
 6.93327;-8.00506;-19.99046;,
 6.02764;-1.66962;-7.78615;,
 6.02765;-1.66962;-5.20145;,
 6.66149;-2.92725;-7.96173;,
 5.13626;-2.92725;-11.48171;,
 6.56233;-1.66962;-2.61676;,
 6.66149;-2.92725;-5.10592;,
 6.56233;-1.66962;-0.03206;,
 7.25226;-2.92725;-2.25011;,
 6.02765;-1.66962;2.55263;,
 7.25227;-2.92725;0.60572;,
 4.71748;-1.66962;5.13733;,
 6.66149;-2.92725;3.46152;,
 4.64721;-1.66962;5.68741;,
 5.13626;-2.92725;6.41820;,
 5.64829;-4.36114;-11.72566;,
 5.64829;-4.36114;-14.61009;,
 7.32513;-4.36114;-7.94341;,
 7.32513;-4.36114;-4.80373;,
 7.97462;-4.36114;-1.66405;,
 7.32513;-4.36114;4.05500;,
 5.64829;-4.36114;8.59138;,
 6.05786;-5.93148;-14.58849;,
 6.05786;-5.93148;-17.68154;,
 6.05786;-5.93148;-11.49542;,
 7.85597;-5.93148;-4.87642;,
 8.55244;-5.93148;-1.50966;,
 7.85597;-5.93148;4.62300;,
 6.05786;-5.93148;9.49338;,
 6.93327;-6.68699;-16.45155;,
 6.93327;-6.68699;-19.99046;,
 6.93327;-6.68699;-12.91260;,
 8.99058;-6.68699;-5.56042;,
 9.78745;-6.68699;-1.70834;,
 8.99058;-6.68699;5.30834;,
 6.93327;-6.68699;10.93559;,
 6.93327;-7.34605;-16.45155;,
 6.93327;-7.34605;-19.99046;,
 6.93327;-7.34605;-12.91260;,
 8.99058;-7.34605;-5.56042;,
 9.78745;-7.34605;-1.70834;,
 8.99058;-7.34605;5.30834;,
 6.93327;-7.34605;10.93559;,
 6.93327;-8.00506;-16.45155;,
 6.93327;-8.00506;-19.99046;,
 6.93327;-8.00506;-12.91260;,
 8.99058;-8.00506;-8.52301;,
 9.78745;-8.00506;-1.70834;,
 8.99058;-8.00506;5.30834;,
 6.93327;-8.00506;10.93559;,
 3.09313;-1.66962;-10.94389;,
 3.09313;-1.11681;-8.56931;,
 6.02765;-1.66962;-5.20145;,
 1.99921;-1.66962;-7.78615;,
 1.99921;-1.11681;-5.20145;,
 -0.01501;-1.11681;-7.79620;,
 -2.02922;-1.66962;-7.78615;,
 -2.02922;-1.11681;-5.20145;,
 -3.12315;-1.66962;-10.94388;,
 -4.04343;-1.11681;-7.79620;,
 -6.05765;-1.66962;-5.20145;,
 4.01342;-1.11681;-5.21151;,
 6.56233;-1.66962;-2.61676;,
 2.17744;-0.42293;-2.61676;,
 -0.01501;-0.42293;-5.21151;,
 -2.20745;-0.42293;-2.61676;,
 -4.04343;-1.11681;-5.21151;,
 -6.59234;-1.66962;-2.61676;,
 4.36989;-1.11681;-2.62682;,
 6.56233;-1.66962;-0.03206;,
 2.17744;-0.42293;-0.03206;,
 -0.01501;-0.42293;-2.62682;,
 -2.20745;-0.42293;-0.03206;,
 -4.39990;-1.11681;-2.62682;,
 -6.59234;-1.66962;-0.03206;,
 4.36989;-1.11681;-0.04212;,
 6.02765;-1.66962;2.55263;,
 1.99921;-0.42293;2.55263;,
 -0.01501;-0.42293;-0.04212;,
 -2.02922;-0.42293;2.55263;,
 -4.39990;-1.11681;-0.04212;,
 -6.05765;-1.66962;2.55263;,
 4.01342;-1.11681;5.13733;,
 4.71748;-1.66962;5.13733;,
 1.99921;-0.42293;5.13733;,
 -0.01501;-0.42293;5.13733;,
 -2.02922;-0.42293;5.13733;,
 -4.04343;-1.11681;5.13733;,
 -4.74750;-1.66962;5.13733;,
 3.09313;-1.66962;6.93739;,
 4.64721;-1.66962;5.68741;,
 1.53906;-1.66962;7.87463;,
 -0.01501;-1.66962;7.87463;,
 -1.56907;-1.66962;7.87463;,
 -3.12315;-1.66962;6.93738;,
 -4.67722;-1.66962;5.68741;,
 6.93327;-8.00506;-16.45155;,
 4.61718;-8.00506;-20.00422;,
 4.61718;-8.00506;-23.54315;,
 2.30108;-8.00506;-16.45155;,
 2.30109;-8.00506;-19.99046;,
 -0.01501;-8.00506;-20.00422;,
 -2.33110;-8.00506;-16.45155;,
 -2.33110;-8.00506;-19.99046;,
 -4.64719;-8.00506;-20.00422;,
 -4.64719;-8.00506;-23.54316;,
 -6.96328;-8.00506;-16.45155;,
 6.93327;-8.00506;-12.91260;,
 4.61718;-8.00506;-16.46534;,
 2.30109;-8.00506;-12.91260;,
 -0.01501;-8.00506;-16.46534;,
 -2.33110;-8.00506;-12.91260;,
 -4.64719;-8.00506;-16.46534;,
 -6.96328;-8.00506;-12.91260;,
 8.99058;-8.00506;-8.52301;,
 4.61718;-8.00506;-12.92637;,
 2.98686;-8.00506;-8.52301;,
 -0.01501;-8.00506;-12.92637;,
 -3.01687;-8.00506;-8.52301;,
 -4.64719;-8.00506;-12.92637;,
 -9.02059;-8.00506;-8.52301;,
 9.78745;-8.00506;-1.70834;,
 5.98872;-8.00506;-8.53801;,
 3.25248;-8.00506;-1.70834;,
 -0.01501;-8.00506;-8.53800;,
 -3.28249;-8.00506;-1.70834;,
 -6.01873;-8.00506;-8.53800;,
 -9.81745;-8.00506;-1.70834;,
 8.99058;-8.00506;5.30834;,
 5.98872;-8.00506;5.30834;,
 2.98686;-8.00506;5.30834;,
 -0.01501;-8.00506;5.30834;,
 -3.01686;-8.00506;5.30834;,
 -6.01873;-8.00506;5.30834;,
 -9.02059;-8.00506;5.30834;,
 6.93327;-8.00506;10.93559;,
 4.61718;-8.00506;12.31668;,
 2.30109;-8.00506;13.35223;,
 -0.01501;-8.00506;13.35223;,
 -2.33110;-8.00506;13.35224;,
 -4.64719;-8.00506;12.31668;,
 -6.96328;-8.00506;10.93559;;
 
 216;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;3,2,14,15;,
 4;2,5,16,14;,
 4;5,7,17,16;,
 4;7,9,18,17;,
 4;9,11,19,18;,
 4;11,13,20,19;,
 4;15,14,21,22;,
 4;14,16,23,21;,
 4;16,17,24,23;,
 4;17,18,25,24;,
 4;18,19,26,25;,
 4;19,20,27,26;,
 4;22,21,28,29;,
 4;21,23,30,28;,
 4;23,24,31,30;,
 4;24,25,32,31;,
 4;25,26,33,32;,
 4;26,27,34,33;,
 4;29,28,35,36;,
 4;28,30,37,35;,
 4;30,31,38,37;,
 4;31,32,39,38;,
 4;32,33,40,39;,
 4;33,34,41,40;,
 4;36,35,42,43;,
 4;35,37,44,42;,
 4;37,38,45,44;,
 4;38,39,46,45;,
 4;39,40,47,46;,
 4;40,41,48,47;,
 4;49,50,51,52;,
 4;50,53,54,51;,
 4;53,55,56,54;,
 4;55,57,58,56;,
 4;57,59,60,58;,
 4;59,61,62,60;,
 4;52,51,63,64;,
 4;51,54,65,63;,
 4;54,56,66,65;,
 4;56,58,67,66;,
 4;58,60,68,67;,
 4;60,62,69,68;,
 4;64,63,70,71;,
 4;63,65,72,70;,
 4;65,66,73,72;,
 4;66,67,74,73;,
 4;67,68,75,74;,
 4;68,69,76,75;,
 4;71,70,77,78;,
 4;70,72,79,77;,
 4;72,73,80,79;,
 4;73,74,81,80;,
 4;74,75,82,81;,
 4;75,76,83,82;,
 4;78,77,84,85;,
 4;77,79,86,84;,
 4;79,80,87,86;,
 4;80,81,88,87;,
 4;81,82,89,88;,
 4;82,83,90,89;,
 4;85,84,91,92;,
 4;84,86,93,91;,
 4;86,87,94,93;,
 4;87,88,95,94;,
 4;88,89,96,95;,
 4;89,90,97,96;,
 4;98,99,100,101;,
 4;99,102,103,100;,
 4;102,104,105,103;,
 4;104,106,107,105;,
 4;106,108,109,107;,
 4;108,110,111,109;,
 4;101,100,112,113;,
 4;100,103,114,112;,
 4;103,105,115,114;,
 4;105,107,116,115;,
 4;107,109,117,116;,
 4;109,111,118,117;,
 4;113,112,119,120;,
 4;112,114,121,119;,
 4;114,115,122,121;,
 4;115,116,123,122;,
 4;116,117,124,123;,
 4;117,118,125,124;,
 4;120,119,126,127;,
 4;119,121,128,126;,
 4;121,122,129,128;,
 4;122,123,130,129;,
 4;123,124,131,130;,
 4;124,125,132,131;,
 4;127,126,133,134;,
 4;126,128,135,133;,
 4;128,129,136,135;,
 4;129,130,137,136;,
 4;130,131,138,137;,
 4;131,132,139,138;,
 4;134,133,140,141;,
 4;133,135,142,140;,
 4;135,136,143,142;,
 4;136,137,144,143;,
 4;137,138,145,144;,
 4;138,139,146,145;,
 4;147,148,149,150;,
 4;148,151,152,149;,
 4;151,153,154,152;,
 4;153,155,156,154;,
 4;155,157,158,156;,
 4;157,159,160,158;,
 4;150,149,161,162;,
 4;149,152,163,161;,
 4;152,154,164,163;,
 4;154,156,165,164;,
 4;156,158,166,165;,
 4;158,160,167,166;,
 4;162,161,168,169;,
 4;161,163,170,168;,
 4;163,164,171,170;,
 4;164,165,172,171;,
 4;165,166,173,172;,
 4;166,167,174,173;,
 4;169,168,175,176;,
 4;168,170,177,175;,
 4;170,171,178,177;,
 4;171,172,179,178;,
 4;172,173,180,179;,
 4;173,174,181,180;,
 4;176,175,182,183;,
 4;175,177,184,182;,
 4;177,178,185,184;,
 4;178,179,186,185;,
 4;179,180,187,186;,
 4;180,181,188,187;,
 4;183,182,189,190;,
 4;182,184,191,189;,
 4;184,185,192,191;,
 4;185,186,193,192;,
 4;186,187,194,193;,
 4;187,188,195,194;,
 4;147,196,197,198;,
 4;196,199,200,197;,
 4;199,104,201,200;,
 4;104,202,203,201;,
 4;202,204,205,203;,
 4;204,61,206,205;,
 4;198,197,207,208;,
 4;197,200,209,207;,
 4;200,201,210,209;,
 4;201,203,211,210;,
 4;203,205,212,211;,
 4;205,206,213,212;,
 4;208,207,214,215;,
 4;207,209,216,214;,
 4;209,210,217,216;,
 4;210,211,218,217;,
 4;211,212,219,218;,
 4;212,213,220,219;,
 4;215,214,221,222;,
 4;214,216,223,221;,
 4;216,217,224,223;,
 4;217,218,225,224;,
 4;218,219,226,225;,
 4;219,220,227,226;,
 4;222,221,228,229;,
 4;221,223,230,228;,
 4;223,224,231,230;,
 4;224,225,232,231;,
 4;225,226,233,232;,
 4;226,227,234,233;,
 4;229,228,235,236;,
 4;228,230,237,235;,
 4;230,231,238,237;,
 4;231,232,239,238;,
 4;232,233,240,239;,
 4;233,234,241,240;,
 4;242,243,244,190;,
 4;243,245,246,244;,
 4;245,247,143,246;,
 4;247,248,249,143;,
 4;248,250,251,249;,
 4;250,252,97,251;,
 4;253,254,243,242;,
 4;254,255,245,243;,
 4;255,256,247,245;,
 4;256,257,248,247;,
 4;257,258,250,248;,
 4;258,259,252,250;,
 4;260,261,254,253;,
 4;261,262,255,254;,
 4;262,263,256,255;,
 4;263,264,257,256;,
 4;264,265,258,257;,
 4;265,266,259,258;,
 4;267,268,261,260;,
 4;268,269,262,261;,
 4;269,270,263,262;,
 4;270,271,264,263;,
 4;271,272,265,264;,
 4;272,273,266,265;,
 4;274,275,268,267;,
 4;275,276,269,268;,
 4;276,277,270,269;,
 4;277,278,271,270;,
 4;278,279,272,271;,
 4;279,280,273,272;,
 4;281,282,275,274;,
 4;282,283,276,275;,
 4;283,284,277,276;,
 4;284,285,278,277;,
 4;285,286,279,278;,
 4;286,287,280,279;;
 
 MeshMaterialList {
  5;
  216;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.000000;0.800000;0.006400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/���b.png";
   }
  }
  Material {
   0.160000;0.160000;0.160000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/���b.png";
   }
  }
  Material {
   0.780800;0.800000;0.000000;0.700000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  201;
  0.634423;0.694231;0.339929;,
  0.397926;0.823823;0.403696;,
  0.133579;0.893962;0.427772;,
  0.000000;0.903889;0.427768;,
  -0.197135;0.867944;0.455864;,
  -0.469288;0.752810;0.461569;,
  0.682429;0.618830;0.389025;,
  0.457863;0.712019;0.532345;,
  0.171524;0.764957;0.620822;,
  -0.000001;0.761961;0.647623;,
  -0.255999;0.757800;0.600170;,
  -0.489397;0.704389;0.514128;,
  0.709180;0.544943;0.447327;,
  0.506173;0.561657;0.654469;,
  0.208425;0.550363;0.808492;,
  -0.000001;0.539604;0.841919;,
  -0.231865;0.588083;0.774853;,
  -0.480250;0.645208;0.594194;,
  0.585703;0.703123;0.403200;,
  0.395836;0.696503;0.598497;,
  0.169519;0.677926;0.715318;,
  -0.000001;0.660477;0.750847;,
  -0.169519;0.677927;0.715317;,
  -0.395835;0.696504;0.598496;,
  0.378714;0.880692;0.284531;,
  0.415123;0.487278;0.768267;,
  0.186951;0.462440;0.866717;,
  0.000001;0.444630;0.895715;,
  -0.186951;0.462441;0.866717;,
  -0.415123;0.487278;0.768266;,
  0.770099;0.000000;0.637925;,
  0.460958;0.000000;0.887422;,
  0.208680;0.000000;0.977984;,
  0.000001;0.000000;1.000000;,
  -0.208680;0.000000;0.977984;,
  -0.460959;0.000000;0.887422;,
  0.770099;0.000000;0.637925;,
  0.208680;0.000000;0.977984;,
  -0.208680;0.000000;0.977984;,
  -0.721975;0.565536;0.398649;,
  -0.782904;0.559492;0.272083;,
  -0.896626;0.382475;0.223103;,
  -1.000000;0.000000;0.000000;,
  -0.998474;-0.017049;-0.052527;,
  -0.966461;0.238782;-0.094536;,
  -0.668991;0.633611;0.388572;,
  -0.843154;0.483279;0.235655;,
  -0.894539;0.428827;0.126129;,
  -0.918920;0.392501;-0.039091;,
  -0.954154;0.290627;-0.071601;,
  -0.941339;0.315944;-0.118577;,
  -0.634865;0.657410;0.405905;,
  -0.790562;0.581129;0.193135;,
  -0.825189;0.564854;-0.001485;,
  -0.832298;0.539393;-0.127809;,
  -0.899058;0.412278;-0.147384;,
  -0.941543;0.313944;-0.122215;,
  -0.585702;0.703124;0.403200;,
  -0.736651;0.653715;0.173211;,
  -0.760881;0.648795;-0.011180;,
  -0.748519;0.642764;-0.163014;,
  -0.804032;0.571819;-0.162958;,
  -0.850589;0.523082;-0.053705;,
  -0.378714;0.880692;0.284531;,
  -0.845994;0.494742;0.198809;,
  -0.871654;0.490121;-0.000988;,
  -0.470911;0.872893;-0.127673;,
  -0.862074;0.474198;-0.178787;,
  -0.909220;0.416315;0.000000;,
  -0.770099;0.000000;0.637925;,
  -0.973256;0.000000;0.229722;,
  -0.999999;0.000000;-0.001661;,
  -0.961787;0.000000;-0.273800;,
  -0.976085;0.000000;-0.217390;,
  -1.000000;0.000000;0.000000;,
  -0.999999;0.000000;-0.001661;,
  -0.961787;0.000000;-0.273800;,
  -0.976085;0.000000;-0.217390;,
  -0.553486;0.801664;-0.225804;,
  -0.150583;0.965603;-0.211980;,
  0.207968;0.952989;-0.220366;,
  -0.000001;0.961442;-0.275008;,
  0.381507;0.888725;-0.254208;,
  -0.329042;0.920971;-0.208672;,
  -0.705833;0.656638;-0.265756;,
  -0.447496;0.834996;-0.320202;,
  0.573460;0.751090;-0.327121;,
  -0.000001;0.925974;-0.377588;,
  0.503188;0.800205;-0.326303;,
  -0.573462;0.751088;-0.327121;,
  -0.769022;0.599303;-0.222352;,
  -0.490677;0.810500;-0.319885;,
  0.579927;0.721630;-0.378068;,
  -0.532784;0.771687;-0.347334;,
  0.532782;0.771688;-0.347334;,
  -0.579927;0.721630;-0.378068;,
  -0.657764;0.739530;-0.142978;,
  -0.115837;0.940954;-0.318100;,
  0.267447;0.895029;-0.356926;,
  -0.201931;0.928770;-0.310820;,
  0.161329;0.922500;-0.350665;,
  -0.292364;0.896604;-0.332602;,
  -0.833676;0.506032;-0.221168;,
  0.111201;0.952198;-0.284524;,
  0.069093;0.945528;-0.318124;,
  -0.000001;0.964431;-0.264335;,
  -0.069094;0.945528;-0.318124;,
  -0.111202;0.952197;-0.284525;,
  -0.958568;0.000000;-0.284863;,
  -0.837707;0.000000;-0.546121;,
  0.837706;0.000000;-0.546121;,
  -0.837706;0.000000;-0.546121;,
  0.837705;0.000000;-0.546122;,
  -0.837706;0.000000;-0.546122;,
  -0.958568;0.000000;-0.284863;,
  -0.837707;0.000000;-0.546121;,
  0.539071;0.811987;-0.223785;,
  0.614356;0.779478;-0.122399;,
  0.626217;0.776285;-0.072351;,
  0.607906;0.794008;0.000621;,
  0.613172;0.776931;0.142823;,
  0.650387;0.720590;0.240306;,
  0.705833;0.656638;-0.265756;,
  0.893152;0.419257;-0.162796;,
  0.895792;0.428749;-0.117181;,
  0.892111;0.449172;-0.048806;,
  0.870562;0.481470;0.101530;,
  0.815169;0.523668;0.247529;,
  0.769022;0.599303;-0.222352;,
  0.938604;0.312255;-0.146693;,
  0.947304;0.278928;-0.157525;,
  0.942937;0.306531;-0.130035;,
  0.927072;0.374768;-0.009269;,
  0.869361;0.439177;0.226574;,
  0.657764;0.739530;-0.142978;,
  0.850588;0.523082;-0.053705;,
  0.844578;0.519451;-0.129843;,
  0.801297;0.577580;-0.155963;,
  0.771910;0.634769;-0.034980;,
  0.736651;0.653714;0.173211;,
  0.487173;0.867653;-0.099202;,
  0.909220;0.416315;0.000000;,
  0.882137;0.456671;-0.115266;,
  0.846420;0.491416;-0.205144;,
  0.869521;0.492360;-0.038914;,
  0.845993;0.494743;0.198809;,
  0.958568;0.000000;-0.284863;,
  1.000000;0.000000;0.000000;,
  0.981776;0.110290;-0.154763;,
  0.954573;0.169861;-0.244821;,
  0.997577;0.060619;-0.034144;,
  0.973256;0.000000;0.229723;,
  0.959578;0.222701;-0.172089;,
  0.908979;0.336291;-0.246302;,
  0.992363;0.121252;-0.022673;,
  -0.018084;0.991448;-0.129245;,
  0.008479;0.979513;-0.201205;,
  -0.000001;0.973104;-0.230368;,
  -0.080759;0.979448;-0.184822;,
  -0.067936;0.991693;-0.109222;,
  0.204159;0.977190;-0.058469;,
  0.157039;0.982127;-0.103760;,
  -0.000000;0.991162;-0.132658;,
  -0.157039;0.982127;-0.103760;,
  -0.204242;0.977676;-0.049345;,
  0.273214;0.961953;-0.000500;,
  0.152633;0.988279;-0.002625;,
  0.000000;1.000000;0.000000;,
  -0.152633;0.988279;-0.002625;,
  -0.273214;0.961953;-0.000500;,
  0.329509;0.942679;0.052720;,
  0.155783;0.987777;0.005261;,
  -0.155783;0.987777;0.005261;,
  -0.329508;0.942680;0.052719;,
  0.391221;0.893784;0.219307;,
  0.153669;0.963250;0.220309;,
  0.000000;0.977256;0.212063;,
  -0.153669;0.963250;0.220309;,
  -0.391220;0.893785;0.219307;,
  0.000000;-1.000000;-0.000000;,
  -0.961787;0.000000;-0.273800;,
  0.579969;0.763261;-0.284725;,
  -0.493318;0.809587;-0.318130;,
  -0.503190;0.800204;-0.326303;,
  -0.563288;0.792378;-0.234188;,
  0.428015;0.839011;-0.335952;,
  0.447496;0.834996;-0.320202;,
  0.490677;0.810500;-0.319885;,
  0.593733;0.705450;-0.387068;,
  -0.552143;0.752044;-0.359955;,
  0.552141;0.752045;-0.359955;,
  -0.593733;0.705450;-0.387068;,
  0.514067;0.789570;-0.335134;,
  -0.837707;0.000000;-0.546121;,
  0.837706;0.000000;-0.546121;,
  -0.837706;0.000000;-0.546121;,
  0.837706;0.000000;-0.546122;,
  -0.264282;0.961590;-0.074163;,
  -0.254630;0.966786;-0.022118;,
  -0.244472;0.969647;0.004191;,
  -0.244305;0.969370;0.025242;;
  216;
  4;0,1,7,6;,
  4;1,2,8,7;,
  4;2,3,9,8;,
  4;3,4,10,9;,
  4;4,5,11,10;,
  4;5,39,45,11;,
  4;6,7,13,12;,
  4;7,8,14,13;,
  4;8,9,15,14;,
  4;9,10,16,15;,
  4;10,11,17,16;,
  4;11,45,51,17;,
  4;12,13,19,18;,
  4;13,14,20,19;,
  4;14,15,21,20;,
  4;15,16,22,21;,
  4;16,17,23,22;,
  4;17,51,57,23;,
  4;18,19,25,24;,
  4;19,20,26,25;,
  4;20,21,27,26;,
  4;21,22,28,27;,
  4;22,23,29,28;,
  4;23,57,63,29;,
  4;36,25,31,30;,
  4;25,26,32,31;,
  4;26,27,33,32;,
  4;27,28,34,33;,
  4;28,29,35,34;,
  4;29,69,69,35;,
  4;30,31,31,36;,
  4;31,32,37,31;,
  4;32,33,33,37;,
  4;33,34,38,33;,
  4;34,35,35,38;,
  4;35,69,69,35;,
  4;39,40,46,45;,
  4;40,41,47,46;,
  4;41,42,48,47;,
  4;42,43,49,48;,
  4;43,44,50,49;,
  4;44,78,84,50;,
  4;45,46,52,51;,
  4;46,47,53,52;,
  4;47,48,54,53;,
  4;48,49,55,54;,
  4;49,50,56,55;,
  4;50,84,90,56;,
  4;51,52,58,57;,
  4;52,53,59,58;,
  4;53,54,60,59;,
  4;54,55,61,60;,
  4;55,56,62,61;,
  4;56,90,96,62;,
  4;57,58,64,63;,
  4;58,59,65,64;,
  4;59,60,66,65;,
  4;60,61,67,66;,
  4;61,62,68,67;,
  4;62,96,102,68;,
  4;69,64,70,69;,
  4;64,65,71,70;,
  4;65,180,72,71;,
  4;180,67,73,72;,
  4;67,68,74,73;,
  4;68,102,108,74;,
  4;69,70,70,69;,
  4;70,71,75,70;,
  4;71,72,76,75;,
  4;72,73,77,76;,
  4;73,74,74,77;,
  4;74,108,114,74;,
  4;78,79,85,84;,
  4;181,80,86,86;,
  4;182,81,87,183;,
  4;81,82,88,87;,
  4;184,83,89,89;,
  4;185,116,122,186;,
  4;84,85,91,90;,
  4;86,86,92,92;,
  4;183,87,93,93;,
  4;87,88,94,94;,
  4;89,89,95,95;,
  4;186,122,128,187;,
  4;90,91,97,96;,
  4;92,92,98,188;,
  4;93,93,99,189;,
  4;94,94,100,190;,
  4;95,95,101,191;,
  4;187,128,134,192;,
  4;96,97,103,102;,
  4;97,98,104,103;,
  4;98,99,105,104;,
  4;99,100,106,105;,
  4;100,101,107,106;,
  4;101,134,140,107;,
  4;102,193,109,108;,
  4;194,194,110,110;,
  4;195,195,111,111;,
  4;112,112,112,112;,
  4;113,113,113,113;,
  4;196,146,146,196;,
  4;108,109,115,114;,
  4;110,110,110,110;,
  4;111,111,111,111;,
  4;112,112,112,112;,
  4;113,113,113,113;,
  4;196,146,146,196;,
  4;116,117,123,122;,
  4;117,118,124,123;,
  4;118,119,125,124;,
  4;119,120,126,125;,
  4;120,121,127,126;,
  4;121,0,6,127;,
  4;122,123,129,128;,
  4;123,124,130,129;,
  4;124,125,131,130;,
  4;125,126,132,131;,
  4;126,127,133,132;,
  4;127,6,12,133;,
  4;128,129,135,134;,
  4;129,130,136,135;,
  4;130,131,137,136;,
  4;131,132,138,137;,
  4;132,133,139,138;,
  4;133,12,18,139;,
  4;134,135,141,140;,
  4;135,136,142,141;,
  4;136,137,143,142;,
  4;137,138,144,143;,
  4;138,139,145,144;,
  4;139,18,24,145;,
  4;146,141,147,146;,
  4;141,142,148,147;,
  4;142,143,149,148;,
  4;143,144,150,149;,
  4;144,145,151,150;,
  4;145,36,30,151;,
  4;146,147,147,146;,
  4;147,148,152,147;,
  4;148,149,153,152;,
  4;149,150,154,153;,
  4;150,151,151,154;,
  4;151,30,36,151;,
  4;116,83,155,117;,
  4;83,184,156,155;,
  4;82,81,157,156;,
  4;81,80,158,157;,
  4;80,79,159,158;,
  4;79,78,197,159;,
  4;117,155,160,118;,
  4;155,156,161,160;,
  4;156,157,162,161;,
  4;157,158,163,162;,
  4;158,159,164,163;,
  4;159,197,198,164;,
  4;118,160,165,119;,
  4;160,161,166,165;,
  4;161,162,167,166;,
  4;162,163,168,167;,
  4;163,164,169,168;,
  4;164,198,199,169;,
  4;119,165,170,120;,
  4;165,166,171,170;,
  4;166,167,167,171;,
  4;167,168,172,167;,
  4;168,169,173,172;,
  4;169,199,200,173;,
  4;120,170,174,121;,
  4;170,171,175,174;,
  4;171,167,176,175;,
  4;167,172,177,176;,
  4;172,173,178,177;,
  4;173,41,40,178;,
  4;121,174,1,0;,
  4;174,175,2,1;,
  4;175,176,3,2;,
  4;176,177,4,3;,
  4;177,178,5,4;,
  4;178,40,39,5;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;,
  4;179,179,179,179;;
 }
 MeshTextureCoords {
  288;
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.333330;0.000000;,
  0.333330;0.166670;,
  0.500000;0.000000;,
  0.500000;0.166670;,
  0.666670;0.000000;,
  0.666670;0.166670;,
  0.833330;0.000000;,
  0.833330;0.166670;,
  1.000000;0.000000;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.500000;1.000000;,
  0.666670;1.000000;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.333330;0.000000;,
  0.333330;0.166670;,
  0.500000;0.000000;,
  0.500000;0.166670;,
  0.666670;0.000000;,
  0.666670;0.166670;,
  0.833330;0.000000;,
  0.833330;0.166670;,
  1.000000;0.000000;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.500000;1.000000;,
  0.666670;1.000000;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.333330;0.000000;,
  0.333330;0.166670;,
  0.500000;0.000000;,
  0.500000;0.166670;,
  0.666670;0.000000;,
  0.666670;0.166670;,
  0.833330;0.000000;,
  0.833330;0.166670;,
  1.000000;0.000000;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.500000;1.000000;,
  0.666670;1.000000;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.333330;0.000000;,
  0.333330;0.166670;,
  0.500000;0.000000;,
  0.500000;0.166670;,
  0.666670;0.000000;,
  0.666670;0.166670;,
  0.833330;0.000000;,
  0.833330;0.166670;,
  1.000000;0.000000;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.500000;1.000000;,
  0.666670;1.000000;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  0.166670;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.333330;0.000000;,
  0.333330;0.166670;,
  0.500000;0.166670;,
  0.666670;0.000000;,
  0.666670;0.166670;,
  0.833330;0.000000;,
  0.833330;0.166670;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.500000;1.000000;,
  0.666670;1.000000;,
  0.833330;1.000000;,
  1.000000;1.000000;,
  0.000000;0.833330;,
  0.166670;0.833330;,
  0.166670;1.000000;,
  0.333330;0.833330;,
  0.333330;1.000000;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.666670;1.000000;,
  0.833330;0.833330;,
  0.833330;1.000000;,
  1.000000;0.833330;,
  0.000000;0.666670;,
  0.166670;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.000000;0.333330;,
  0.166670;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.000000;0.166670;,
  0.166670;0.166670;,
  0.333330;0.166670;,
  0.500000;0.166670;,
  0.666670;0.166670;,
  0.833330;0.166670;,
  1.000000;0.166670;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.333330;0.000000;,
  0.500000;0.000000;,
  0.666670;0.000000;,
  0.833330;0.000000;,
  1.000000;0.000000;;
 }
}
