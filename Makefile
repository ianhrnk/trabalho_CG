CC = g++
FLAGS = -lGLEW -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
OBJ_DIR = src/obj

all: criar_pasta_obj src/obj/ElementBuffer.o src/obj/Main.o src/obj/Model.o	\
	 src/obj/Renderer.o src/obj/Scene.o src/obj/Shader.o src/obj/VertexArray.o \
	 src/obj/VertexBuffer.o Main

criar_pasta_obj:
	@mkdir -p $(OBJ_DIR)

src/obj/ElementBuffer.o: src/ElementBuffer.cpp src/ElementBuffer.h
	@echo compilando $@
	@$(CC) -c $< $(FLAGS) -o $@

src/obj/Main.o: src/Main.cpp src/Scene.h src/Shader.h src/Model.h src/Renderer.h
	@echo compilando $@
	@$(CC) -c $< $(FLAGS) -o $@

src/obj/Model.o: src/Model.cpp src/Model.h src/VertexArray.h \
				 src/VertexBuffer.h src/ElementBuffer.h
	@echo compilando $@
	@$(CC) -c $< $(FLAGS) -o $@

src/obj/Renderer.o: src/Renderer.cpp src/Renderer.h src/Scene.h src/Shader.h
	@echo compilando $@
	@$(CC) -c $< $(FLAGS) -o $@

src/obj/Scene.o: src/Scene.cpp src/Scene.h src/Model.h
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

Main: src/obj/ElementBuffer.o src/obj/Main.o src/obj/Model.o src/obj/Scene.o \
	  src/obj/Shader.o src/obj/Renderer.o src/obj/VertexArray.o src/obj/VertexBuffer.o
	@echo compilando $@
	@$(CC) src/obj/*.o $(FLAGS) -o $@

clean:
	@rm -rf src/obj
	@rm Main
