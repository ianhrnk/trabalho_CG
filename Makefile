CXX = g++
CXXFLAGS = -lGLEW -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -Wall

BIN := Main
OBJ_DIR = build
OBJ = $(OBJ_DIR)/Camera.o $(OBJ_DIR)/ElementBuffer.o $(OBJ_DIR)/Main.o $(OBJ_DIR)/Reader.o \
	  $(OBJ_DIR)/SceneObject.o $(OBJ_DIR)/Scene.o $(OBJ_DIR)/Shader.o $(OBJ_DIR)/Renderer.o \
	  $(OBJ_DIR)/VertexArray.o $(OBJ_DIR)/VertexBuffer.o

all: criar_pasta_obj $(BIN)

criar_pasta_obj:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/Camera.o: src/Camera.cpp src/Camera.h
	@echo Compilando $<
	@$(CXX) -c $< $(CXXFLAGS) -o $@

$(OBJ_DIR)/ElementBuffer.o: src/ElementBuffer.cpp src/ElementBuffer.h
	@echo Compilando $<
	@$(CXX) -c $< $(CXXFLAGS) -o $@

$(OBJ_DIR)/Main.o: src/Main.cpp src/Renderer.h
	@echo Compilando $<
	@$(CXX) -c $< $(CXXFLAGS) -o $@

$(OBJ_DIR)/Reader.o: src/Reader.cpp src/Reader.h
	@echo Compilando $<
	@$(CXX) -c $< $(CXXFLAGS) -o $@

$(OBJ_DIR)/Renderer.o: src/Renderer.cpp src/Renderer.h src/Scene.h src/Shader.h
	@echo Compilando $<
	@$(CXX) -c $< $(CXXFLAGS) -o $@

$(OBJ_DIR)/Scene.o: src/Scene.cpp src/Scene.h src/Camera.h src/SceneObject.h
	@echo Compilando $<
	@$(CXX) -c $< $(CXXFLAGS) -o $@

$(OBJ_DIR)/SceneObject.o: src/SceneObject.cpp src/SceneObject.h src/Reader.h \
					   src/VertexArray.h src/VertexBuffer.h src/ElementBuffer.h
	@echo Compilando $<
	@$(CXX) -c $< $(CXXFLAGS) -o $@

$(OBJ_DIR)/Shader.o: src/Shader.cpp src/Shader.h
	@echo Compilando $<
	@$(CXX) -c $< $(CXXFLAGS) -o $@

$(OBJ_DIR)/VertexArray.o: src/VertexArray.cpp src/VertexArray.h
	@echo Compilando $<
	@$(CXX) -c $< $(CXXFLAGS) -o $@

$(OBJ_DIR)/VertexBuffer.o: src/VertexBuffer.cpp src/VertexBuffer.h
	@echo Compilando $<
	@$(CXX) -c $< $(CXXFLAGS) -o $@

$(BIN): $(OBJ)
	@echo Compilando $@
	@$(CXX) $(OBJ) $(CXXFLAGS) -o $@

.PHONY: all clean

clean:
	@rm -rf $(OBJ_DIR) $(BIN)
