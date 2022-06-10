# sdlRasterizer
2nd c++ project

rasterizer made only using sdl and pure software/CPU rendering no GPU

sdl only used for creating window, drawing individual pixels on that window, and loading .bmp

rasterizer features:
- Wireframe rendering
- Illumination/shading via point light on camera
- Simple .OBJ file parser/renderer (can only parse/render obj with vertices and triangular faces)
- Simple clipping
- Back-face culling
- 3d models: Cube, Teapot, and Cow
- Adding 3d models to scene with custom postion, rotation, and scale (via code)
- Texture mapping of Cube model only
- FPS controls
renders 15-100~ fps on average (depends on scene and rendering method)

# Demo
### Cube Wireframe and Texture Mapped Rendering with position and rotation applied to cubes, FPS controls, and simple clipping
#### <i>Rendering with texture is kinda buggy</i>
<div>
  <img src="https://github.com/tenick/sdlRasterizer/blob/master/gitResources/rasterizerDemo1.gif" width="500" height="500"/>
  <img src="https://github.com/tenick/sdlRasterizer/blob/master/gitResources/rasterizerDemo6.gif" width="500" height="500"/>
</div>

### Cow Wireframe and Shaded Rendering

<div>
  <img src="https://github.com/tenick/sdlRasterizer/blob/master/gitResources/rasterizerDemo2.gif" width="500" height="500"/>
  <img src="https://github.com/tenick/sdlRasterizer/blob/master/gitResources/rasterizerDemo4.gif" width="500" height="500"/>
</div>

### Teapot Wireframe and Shaded Rendering

<div>
  <img src="https://github.com/tenick/sdlRasterizer/blob/master/gitResources/rasterizerDemo3.gif" width="500" height="500"/>
  <img src="https://github.com/tenick/sdlRasterizer/blob/master/gitResources/rasterizerDemo5.gif" width="500" height="500"/>
</div>

<div>
  ### Simple scene demo with shaded rendering
  <img src="https://github.com/tenick/sdlRasterizer/blob/master/gitResources/rasterizerDemo5.gif" width="1000" height="1000"/>
</div>
