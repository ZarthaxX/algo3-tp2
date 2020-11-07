clean: 
	rm main
all:
	g++ src/main.cpp src/heuristicasGolosas/expansivo/expansivo.cpp src/heuristicasGolosas/secuencial/secuencial.cpp src/tabuSearch/tabuSearch.cpp src/coloringScoreVerifier/coloringScoreVerifier.cpp -o main