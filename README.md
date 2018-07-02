# f2src
Files To Source (f2src) - A cross-platform program for generating source files with file data.

###NOTE: This Readme is a work in progress. It will be finished in a few days.
`Call: ./f2fmt -h for a basic program description`

I created this program to be able to embed my files into my executable, but at the same time have a structure of the files in memory.
This is done using namespaces to simulate folders. Alle folders are shown as lower-case, while files are shown as upper-case, so it will be easy to
determine what's what. 

```
All files are generated with a '_' prefix, to make sure the file name is generated safely (spaces. If you however have weird letters in the file name, chances are the variable names get weird as a result. Files do have a basic replace of common characters that are okay for file names, but not for variable names, and the same goes for folder, but at the time being, because folders never has a '_' added in the front, a folder used CANNOT have a number as the first character.
```

There are plenty of C++ libraries that are able to load files from memory, no matter what kind of files you are using inside your 
appllication. Pictures, music, xml, json, you name it!

####Example how to use the data from the produced source files to load image from memory (using the SFML library):
```c++
sf::Texture texture;
sf::Sprite sprite;	
texture.loadFromMemory(files_mapper::test_files::sprites::players::_MARIO_PNG, files_mapper::test_files::sprites::players::_MARIO_PNG_SIZE);
sprite.setTexture(m_texture);//*m_texture
sprite.setOrigin((float)m_texture.getSize().x / 2, (float)m_texture.getSize().y / 2);
```
This example is using data generated from the files under the "test_files" folder.