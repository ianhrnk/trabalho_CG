CC = g++
FLAGS = -lGLEW -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -Wall
OBJ_DIR = src/obj

all: criar_pasta_obj src/obj/Camera.o src/obj/ElementBuffer.o src/obj/Main.o \
	 src/obj/SceneObject.o src/obj/Reader.o src/obj/Renderer.o src/obj/Scene.o \
	 src/obj/Shader.o src/obj/VertexArray.o src/obj/VertexBuffer.o Main

criar_pasta_obj:
	@mkdir -p $(OBJ_DIR)

src/obj/Camera.o: src/Camera.cpp src/Camera.h
	@echo compilando $@
	@$(CC) -c $< $(FLAGS) -o $@

src/obj/ElementBuffer.o: src/ElementBuffer.cpp src/ElementBuffer.h
	@echo compilando $@
	@$(CC) -c $< $(FLAGS) -o $@

src/obj/Main.o: src/Main.cpp src/Renderer.h
	@echo compilando $@
	@$(CC) -c $< $(FLAGS) -o $@

src/obj/Reader.o: src/Reader.cpp src/Reader.h
	@echo compilando $@
	@$(CC) -c $< $(FLAGS) -o $@

src/obj/Renderer.o: src/Renderer.cpp src/Renderer.h src/Scene.h src/Shader.h
	@echo compilando $@
	@$(CC) -c $< $(FLAGS) -o $@

src/obj/Scene.o: src/Scene.cpp src/Scene.h src/Camera.h src/SceneObject.h
	@echo compilando $@
	@$(CC) -c $< $(FLAGS) -o $@

src/obj/SceneObject.o: src/SceneObject.cpp src/SceneObject.h src/Reader.h \
					   src/VertexArray.h src/VertexBuffer.h src/ElementBuffer.h
	@echo compilando $@
	@$(CC) -c $< $(FLAGS) -o $@

src/obj/Shader.o: src/Shader.cpp src/Shader.h
	@echo compilando $@
	@$(CC) -c $< $(FLAGS) -o $@

src/obj/VertexArray.o: src/VertexArray.cpp src/VertexArray.h
	@echo compilando $@
	@$(CC) -c $< $(FLAGS) -o $@

src/obj/VertexBuffer.o: src/VertexBuffer.cpp src/VertexBuffer.h
	@echo compilando $@
	@$(CC) -c $< $(FLAGS) -o $@

Main: src/obj/Camera.o src/obj/ElementBuffer.o src/obj/Main.o src/obj/Reader.o \
	  src/obj/SceneObject.o src/obj/Scene.o src/obj/Shader.o src/obj/Renderer.o \
	  src/obj/VertexArray.o src/obj/VertexBuffer.o
	@echo compilando $@
	@$(CC) src/obj/*.o $(FLAGS) -o $@

clean:
	@rm -rf src/obj
	@rm Main
