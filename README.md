# turn-engine

Minimalist 2D game engine

## Rules

Please locate public headers (that might be included in game project) in `turn-engine/include` folder.
Private headers (used only in that library) and their implementation must be located in `turn-engine/src`

## Installation

Not implemented for now

## Docs

### SDL2 Wrapper

Most of the most used SDL2 functions are wrapped in C++ classes.

| Name                 | Type      | Description                                                                                                               | Implemented? | constexpr implementation |
|----------------------|-----------|---------------------------------------------------------------------------------------------------------------------------|--------------|--------------------------|
| SDL2                 | class     | Class made for SDL2 initialization                                                                                        | Yes          | Yes                      |
| TTF                  | class     | Class made for SDL2 fonts extension                                                                                       | Yes          | Yes                      |
| IMG                  | class     | Class made for SDL2 images extension                                                                                      | Yes          | Yes                      |
| Font                 | class     | Class that wraps SDL_ttf extension                                                                                        | Partly       | No                       |
| Audio?               | class     | Class that wraps SDL_mixer extension                                                                                      | No           | No                       |
| MessageBox           | class     | Class that wraps SDL_MessageBox and functions related to it                                                               | Yes          | Yes                      |
| BasicPaletteView     | class     | Class which wraps SDL_Palette. It used when colors are coded with 1 byte. Don't use it                                    | Yes          | Yes                      |
| BasicPixelFormatView | class     | Class which wraps SDL_PixelFormat. Used to describe pixel format                                                          | Yes          | Yes                      |
| Surface              | class     | Class which wraps SDL_Surface and all functions related to it                                                             | Yes          | Yes                      |
| Texture              | class     | Class which wraps SDL_Texture and all functions related to it                                                             | Yes          | Yes                      |
| RendererInfo         | class     | Class which return information anout renderer                                                                             | Yes          | Yes                      |
| Renderer             | class     | Class which wraps renderer and all functions related to it.  Renderer is used in Drawer                                   | Yes          | Yes                      |
| Rect                 | class     | Class which wraps SDL_Rect and implements some rectangle specific funcs                                                   | Yes          | Yes                      |
| Point                | class     | Class which wraps SDL_Point and implements some point specific funcs                                                      | Yes          | Yes                      |
| TextureLock          | class     | Class which used to lock texture with "streaming" type when you changing it. Must be used when game is multithreaded.     | Yes          | Yes                      |
| Window               | class     | Class which describes SDL_Window and all function related to it                                                           | Yes          | Yes                      |
| event_queue          | struct    | Structure which used to poll events                                                                                       | Yes          | Yes                      |
| xy                   | struct    | Structure which describes point                                                                                           | Yes          | Yes                      |
| wh                   | struct    | Structure which describes rectangle props (width, height)                                                                 | Yes          | Yes                      |
| rgb                  | struct    | Structure which describes color (without alpha var)                                                                       | Yes          | Yes                      |
| rgba                 | struct    | Structure which describes color (with alpha var)                                                                          | Yes          | Yes                      |
| Color                | namespace | Namespace with some colors, defined with rgba<> structure                                                                 | Yes          | Yes                      |
| SDLInitFlags         | enum      | Enumeration with SDL2 initialization flags                                                                                | Yes          | Yes                      |
| IMGInitFlags         | enum      | Enumeration with SDL_image extension initialization flags                                                                 | Yes          | Yes                      |
| MessageBoxFlags      | enum      | Enumeration with MessageBox initialization flags                                                                          | Yes          | Yes                      |
| WindowFlags          | enum      | Enumeration with Window initialization flags                                                                              | Yes          | Yes                      |
| RendererFlags        | enum      | Enumeration with Renderer initialization flags                                                                            | Yes          | Yes                      |
| BlendMode            | enum      | Enumeration of blend modes that used with Renderer. Blend mode means the way how alpha is counted when rendering textures | Yes          | Yes                      |
| FullscreenFlags      | enum      | Enumeration with window types. There are some duplicates of WindowFlags                                                   | Yes          | Yes                      |
| TextureAccess        | enum      | Enumeration of texture access patterns (static, streaming or target)                                                      | Yes          | Yes                      |
| PixelFormatEnum      | enum      | Enumeration with pixel formats (like rgb or bgr, rgba, etc..)                                                             | Yes          | Yes                      |
| PixelType            | enum      | Enumeration with pixel type formats                                                                                       | Yes          | Yes                      |
| PixelOrder           | enum      | Enumeration with pixel order types. That means ordering channels or bits in the pixel format                              | Yes          | Yes                      |
| PixelLayout          | enum      | Enumeration with bit patterns of the pixel format                                                                         | Yes          | Yes                      |
| RendererFlip         | enum      | Enumeration with texture flip flags                                                                                       | Yes          | Yes                      |
