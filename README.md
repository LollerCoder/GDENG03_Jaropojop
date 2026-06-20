Made By: Jairo Rio M. Jaropojop

Entry File:Main.cpp

Include in Project>Linker>Input:
d3d11.lib
d3dcompiler.lib
Ole32.lib
winmm.lib
xaudio2.lib

If it has a problem with entrypoints its probably the shaders.
Right click and HLSL Compiler Entry point Name and change the field to the following:
For PixelShader its 'psmain'
For VertexShader its 'vsmain'
