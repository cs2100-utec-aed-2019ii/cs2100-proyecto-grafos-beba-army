#include <iostream>
#include <map>
#include "grafo.h"

#define ANCHO	600
#define ALTO	600
#define PROFUNDIDAD 100

#define ORADIUS 30
#define DURATION 10

float rotacion = 0.0;

using namespace std;

//#ifdef OGL

Grafo<pair<float,float>,false>* glutGraph = new Grafo<pair<float,float>,false>(2);
map<pair<float,float>,bool> colores;
pair<float,float> root;

GLvoid initGL(){
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

GLvoid window_reshape(GLsizei width, GLsizei height){
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, ANCHO, 0.0f, ALTO, 0.0f, PROFUNDIDAD);
	glMatrixMode(GL_MODELVIEW);
//gluLookAt(0,50, 100, 0,0,0, 0, 1, 0);

}

GLvoid window_key(unsigned char key, int x, int y){
	switch (key) {
	case 27:
		exit(1);
		break;

	default:
		break;
	}
}

void Timer	(int value){ // intervalo en miliseg  
	glutPostRedisplay	(	); 
	//actualizar(); //ACTUALIZAMOS los BOIDS
  //rotacion++;
    glutTimerFunc		(DURATION,Timer, 10);  
}

/*
GLvoid callback_mouse(int button, int state, int x, int y){
	if (http://www.cplusplus.com/reference/queue/priority_queue/?kw=priority_queue(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
		//boids.push_back(boid(x,600-y));
		//predador =  vector_t(x, 600-y,0);
	}
}
*/

GLvoid window_display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-ANCHO, ANCHO, -ANCHO, ALTO, 0.0f, PROFUNDIDAD);

  char opcion;
  float node1_x, node1_y, node2_x, node2_y, weight;

  int numNodes = glutGraph->getNodes().size();
  int numEdges = glutGraph->getEdges().size();

  for(int i = 0; i < numNodes; i++){
    glPushMatrix();
    glTranslatef(glutGraph->getNodes()[i]->value.first,glutGraph->getNodes()[i]->value.second,0);
    //cout<<"Node drawn in: "<<glutGraph->getNodes()[i]->value.first<<","<<glutGraph->getNodes()[i]->value.second<<"\n";
    if(colores[glutGraph->getNodes()[i]->value]){
      glColor3f(0.9,0.3,0.2);
    }
    else{
      glColor3f(1,1,1);
    }
    glutSolidSphere(20,10,10);
    glPopMatrix();
  }

    for(int i = 0; i < numEdges; i++){
    glPushMatrix();

    glBegin(GL_LINES);
    if(colores[glutGraph->getEdges()[i]->start] && colores[glutGraph->getEdges()[i]->end]){
      glColor3f(0.9,0.3,0.2);
    }
    else{
      glColor3f(1,1,1);
    }
    glVertex2f(glutGraph->getEdges()[i]->start.first,glutGraph->getEdges()[i]->start.second);
    glVertex2f(glutGraph->getEdges()[i]->end.first,glutGraph->getEdges()[i]->end.second);
    glEnd();

    glPopMatrix();
  }


	// glPushMatrix();
	// glRotatef(-rotacion, 0 , 0 , 1);
	// glTranslatef(ANCHO/4, ALTO/4,0);
	// glutWireSphere(30,10,10);
	// glPopMatrix();

	// glPushMatrix();
	// glRotatef(3*rotacion, 0 , 0 , 1);
	// glTranslatef(ANCHO/2.5, ALTO/2.5,0);
	// glutWireSphere(45,10,10);
	// glPopMatrix();
	



	glutSwapBuffers();
	glFlush();
  cout<<"OPCIONES: \nn: insertar nodo.\ne: insertar edge.\ns: seleccionar nodos.\nb: borrar nodo.\nd: borrar edge.\nx: guardar grafo.\n2: Bipartite check.\nh: neighborhood.\n";

  cin>>opcion;

  switch(opcion){
    case 'n':{
      cout<<"Coordenada x: ";
      cin>>node1_x;
      cout<<"\nCoordenada y: ";
      cin>>node1_y;
      cout<<"\n";
      glutGraph->addNode(pair<float,float>(node1_x,node1_y));
      break;
    }
    case 'e':{
      cout<<"Nodo 1:\nCoordenada x: ";
      cin>>node1_x;
      cout<<"\nCoordenada y: ";
      cin>>node1_y;
      cout<<"\n";
      cout<<"Nodo 2:\nCoordenada x: ";
      cin>>node2_x;
      cout<<"\nCoordenada y: ";
      cin>>node2_y;
      cout<<"\nPeso: (-1 para peso automatico.)";
      cin>>weight;
      cout<<"\n"; 
      if(weight == -1){
        cout<<"No weight!\n";
        glutGraph->addEdge(pair<float,float>(node1_x,node1_y),pair<float,float>(node2_x,node2_y));
      }
      else{
        glutGraph->addEdge(pair<float,float>(node1_x,node1_y),pair<float,float>(node2_x,node2_y),weight);  
      } 
      break;  

    }
    case 's':{

      colores.clear();

      cout<<"Nodo 1:\nCoordenada x: ";
      cin>>node1_x;
      cout<<"\nCoordenada y: ";
      cin>>node1_y;
      cout<<"\n";
      cout<<"Nodo 2:\nCoordenada x: ";
      cin>>node2_x;
      cout<<"\nCoordenada y: ";
      cin>>node2_y;
      cout<<"\n";

  queue<pair<float,float>> nodos;
  map<pair<float,float>,pair<float,float>> camino; 
	vector<pair<float,float>> visited;
  bool found = false;
	pair<float,float> current;

	nodos.push(pair<float,float>(node1_x,node1_y));

	visited.push_back(pair<float,float>(node1_x,node1_y));

  pair<float,float> find = pair<float,float>(node2_x,node2_y);

	cout<<"\n";

	while(!nodos.empty()){

		current = nodos.front();

		//cout<<"Current node: ("<<current.first<<","<<current.second<<") looking for: ("<<find.first<<","<<find.second<<")\n";	

		nodos.pop();

		if(current.first == find.first && current.second == find.second){
				found = true;
			}

		for(auto edge: glutGraph->getEdges()){
			if(edge->start == current && !glutGraph->findEdgePair(visited, edge->end)){
				//cout<<"Inserting from edge: ("<<current.first<<","<<current.second<<") -> ("<<edge->end.first<<","<<edge->end.second<<")\n";
					nodos.push(edge->end);
					visited.push_back(edge->end);
          camino[edge->end] = edge->start;
			}
		}
	}

	

  if(found){
    current = pair<float,float>(node2_x,node2_y);
    while(current != pair<float,float>(node1_x,node1_y)){
      //cout<<"Pintando: ("<<current.first<<","<<current.second<<")\n";
      colores[current] = true;
      current = camino[current];
    }
  
    colores[current] = true; 
  }


      break;
    }
    case 'b':{
      cout<<"Coordenada x: ";
      cin>>node1_x;
      cout<<"\nCoordenada y: ";
      cin>>node1_y;
      glutGraph->deleteNode(pair<float,float>(node1_x,node1_y));
      colores.clear();
      break;
    }
    case 'h':{

      colores.clear();
      cout<<"Coordenada x: ";
      cin>>node1_x;
      cout<<"\nCoordenada y: ";
      cin>>node1_y;
      root = pair<float,float>(node1_x, node1_y);
      vector<pair<float,float>> neighbors = glutGraph->getNeighbors(pair<float,float>(node1_x,node1_y));
      colores[pair<float,float>(node1_x,node1_y)] = true;

      for(auto node: neighbors){
        if(glutGraph->inNeighborhood(pair<float,float>(node1_x,node1_y),pair<float,float>(node.first,node.second))){
          colores[pair<float,float>(node.first,node.second)] = true;
        }

      }      
      break;
    }
    case 'd':{
      cout<<"Nodo 1:\nCoordenada x: ";
      cin>>node1_x;
      cout<<"\nCoordenada y: ";
      cin>>node1_y;
      cout<<"\n";
      cout<<"Nodo 2:\nCoordenada x: ";
      cin>>node2_x;
      cout<<"\nCoordenada y: ";
      cin>>node2_y; cout<<"\n"; glutGraph->deleteEdge(pair<float,float>(node1_x,node1_y),pair<float,float>(node2_x,node2_y)); colores.clear(); break; }
    case 'x':{
      glutGraph->save();
      break;
    }
    case '2':{
      if(glutGraph->bipartite()){
        cout<<"Es bipartito.\n";
        }
        else{
          cout<<"No es bipartito.\n";
        }
        break;
    }
    case 'g':{
      cout<<"Nodo 1:\nCoordenada x: ";
      cin>>node1_x;
      cout<<"\nCoordenada y: ";
      cin>>node1_y;
      cout<<"Grado: "<<glutGraph->nodeGrade(pair<float,float>(node1_x,node1_y));
      break;
    }

		case 'c':{
			if (glutGraph->connected())
				cout<<" == Es conexo \n";
			else
				cout << " NO es conexo \n";
			break;
		}
		
		case 'k':{
			auto nodGrafoKruskal = glutGraph->mst_kruskal();
			cout << "================Kruskal: \n";
			for (auto i : nodGrafoKruskal){
				cout << "(" << i->start.first << "," << i->start.second << ") -> " << "(" << i->end.first << "," << i->end.second << ") || ";
			}
			break;
		}
		
    default:{
      cout<<"Opcion invalida.\n";
      break;
    }


  }

}

//#endif





int main(int argc, char* argv[]){

#ifndef OGL
    Grafo<pair<float,float>,false>* nodGrafo = new Grafo<pair<float,float>,false>();
    Grafo<pair<float,float>,true>* test = new Grafo<pair<float,float>,true>(2);

    nodGrafo->addNode(pair<float,float>(0,0));
    nodGrafo->addNode(pair<float,float>(0,-10));
    nodGrafo->addNode(pair<float,float>(0,10));
    nodGrafo->addNode(pair<float,float>(5,-5));
    nodGrafo->addNode(pair<float,float>(5,0));
    nodGrafo->addNode(pair<float,float>(5,5));
    nodGrafo->addNode(pair<float,float>(-5,-5));
    nodGrafo->addNode(pair<float,float>(-5,0));
    nodGrafo->addNode(pair<float,float>(-5,5));

    nodGrafo->addEdge({0,0}  ,{5,0}  ,2);    
    nodGrafo->addEdge({0,0}  ,{-5,0} ,6);    
    nodGrafo->addEdge({0,0}  ,{-5,-5},7);    
    nodGrafo->addEdge({0,10} ,{5,5}  ,9);    
    nodGrafo->addEdge({0,10} ,{-5,5} ,10);    
    nodGrafo->addEdge({0,-10},{5,-5} ,4);    
    nodGrafo->addEdge({0,-10},{-5,-5},8);    
    nodGrafo->addEdge({5,-5} ,{5,0}  ,8);    
    nodGrafo->addEdge({5,-5} ,{-5,-5},11);    
    nodGrafo->addEdge({5,0}  ,{5,5}  ,7);    
    nodGrafo->addEdge({5,0}  ,{-5,5} ,4);    
    nodGrafo->addEdge({5,5}  ,{-5,5} ,14);    
    nodGrafo->addEdge({-5,-5},{-5,0} ,2);    
    nodGrafo->addEdge({-5,0} ,{-5,5} ,1);    
		


		/*
		==========
		  Pruebas
		==========
		auto prim = nodGrafo->mst_prim();
		cout << "================Prim: \n";
		for (auto i : prim)
			cout << "(" << i->start.first << "," << i->start.second << ") -> " << "(" << i->end.first << "," << i->end.second << ") || ";

		auto nodGrafoKruskal = nodGrafo->mst_kruskal();
		cout << "================Kruskal: \n";
		for (auto i : nodGrafoKruskal){
			cout << "(" << i->start.first << "," << i->start.second << ") -> " << "(" << i->end.first << "," << i->end.second << ") || ";
		}
		
		cout << "============ density: " << nodGrafo->density() << "\n" ;
    cout<<"===========Try to loop: \n";
    nodGrafo->addEdge({0,0},{0,0},4);
 
		cout << "=========Edge weights:" << endl;
		auto sorted_edges = nodGrafo->non_decreasing_edges();
		for (auto i : sorted_edges)
		 cout << i->weight << " ";

		===================
		 BFS and DFS tests
		===================
    cout<<"BFS for 0 to 3: "<<nodGrafo->bfs({0,0},{})<<endl;
    cout<<"BFS for 0 to 4: "<<nodGrafo->bfs(pair<float,float>(0,0),pair<float,float>(4,4))<<endl;

    cout<<"DFS for 0 to 3: "<<nodGrafo->dfs(pair<float,float>(0,0),pair<float,float>(3,3))<<endl;
    cout<<"DFS for 0 to 4: "<<nodGrafo->dfs(pair<float,float>(0,0),pair<float,float>(4,4))<<endl;

		cout << "LISTADO DE PUNTOS "<<endl;
		cout << nodGrafo->connected() << "\n";

    cout<<"DeleteNode test: \n";
    nodGrafo->deleteNode(pair<float,float>(1,1));

    cout<<"BFS for 0 to 3: "<<nodGrafo->bfs(pair<float,float>(0,0),pair<float,float>(3,3))<<endl;//false
    cout<<"DFS for 0 to 3: "<<nodGrafo->dfs(pair<float,float>(0,0),pair<float,float>(3,3))<<endl;//false

    nodGrafo->addEdge(pair<float,float>(4,4),pair<float,float>(2,2),0.3);
    nodGrafo->addEdge(pair<float,float>(0,0),pair<float,float>(4,4),0.3);

    cout<<"DeleteEdge test: \n";

    cout<<"BFS for 0 to 3: "<<nodGrafo->bfs(pair<int,int>(0,0),pair<int,int>(3,3))<<endl;
    nodGrafo->deleteEdge(pair<int,int>(0,0),pair<int,int>(4,4));
    cout<<"BFS for 0 to 3: "<<nodGrafo->bfs(pair<int,int>(0,0),pair<int,int>(3,3))<<endl;

    cout<<"BFS for 0 to 3: "<<nodGrafo->bfs(pair<float,float>(0,0),pair<float,float>(3,3))<<endl;
    nodGrafo->deleteEdge(pair<float,float>(0,0),pair<float,float>(4,4));
    cout<<"BFS for 0 to 3: "<<nodGrafo->bfs(pair<float,float>(0,0),pair<float,float>(3,3))<<endl;
    nodGrafo->addEdge(pair<float,float>(0,0),pair<float,float>(4,4),0.3);

    nodGrafo->save();

    Grafo<pair<float,float>,true>* test = new Grafo<pair<float,float>,true>(3);

    auto neighbors = nodGrafo->getNeighbors(pair<float,float>(4,4));

    cout<<"Neighbors of (4,4):\n";
    for(auto neighbor: neighbors){
      cout<<neighbor.first<<","<<neighbor.second<<"\n";
    }

    cout<<"Neighborhood test (0,0) and (4,4): "<<nodGrafo->inNeighborhood(pair<float,float>(0,0),pair<float,float>(4,4))<<"\n";
    nodGrafo->addEdge(pair<float,float>(0,0),pair<float,float>(3,3),0.2);
    cout<<"Neighborhood test (0,0) and (4,4): "<<nodGrafo->inNeighborhood(pair<float,float>(0,0),pair<float,float>(4,4))<<"\n";

    cout<<"\n\nBipartite: "<<test->bipartite();

		*/

#endif

#ifdef OGL
  //OPENGL TESTS=========================================================


  // glutGraph->addNode(pair<float,float>(100,100));
  // glutGraph->addNode(pair<float,float>(-100,-100));
  // glutGraph->addNode(pair<float,float>(500,500));
  // glutGraph->addEdge(pair<float,float>(500,500),pair<float,float>(100,100));


  glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(ANCHO, ALTO);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Grafo");
	initGL();
	glEnable(GL_TEXTURE_2D);
	glutDisplayFunc(&window_display);
	glutReshapeFunc(&window_reshape);
	glutKeyboardFunc(&window_key);
	glutTimerFunc(DURATION, Timer, 1);
	glutMouseFunc(&callback_mouse);
	glutMainLoop();

#endif
  return 0;
}   

