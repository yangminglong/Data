// vtkbooltest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"


#include "vtkSTLReader.h"
#include "vtkPolyDataBooleanFilter.h" 

#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkPlaneCollection.h"
#include "vtkPoints.h"
#include "vtkDataArray.h"
#include "vtkPlanes.h"
#include "vtkThreadedSynchronizedTemplatesCutter3D.h"
#include "vtkCubeSource.h"
#include "vtkPolyDataBooleanFilter.h"
#include "vtkDoubleArray.h"
#include "vtkByteSwap.h"
#include "vtkIdTypeArray.h"
#include "vtkPolygon.h"
#include "vtkTriangle.h"
#include "vtkAlgorithmOutput.h"
#include "vtkFloatArray.h"
#include "vtkSTLWriter.h"

#include "vtkNew.h"

int main()
{
  vtkNew<vtkSTLReader> pReaderA;
  pReaderA->SetFileName("../bunny.stl"); 
  pReaderA->Update();

  vtkNew<vtkSTLReader> pReaderB ;
  pReaderB->SetFileName("../punching.stl"); 
  pReaderB->Update();

  vtkNew<vtkPolyDataBooleanFilter> bf;
  bf->SetInputData(0, pReaderA->GetOutput());
  bf->SetInputData(1, pReaderB->GetOutput());
  bf->SetOperModeToDifference();
  bf->Update();

  vtkNew<vtkPolyDataMapper> polyDataMapper;
  polyDataMapper->SetInputData(bf->GetOutput());

  vtkNew<vtkActor> polyDataActor;
  polyDataActor->SetMapper(polyDataMapper);
  polyDataActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);

  vtkNew<vtkRenderer> ren1;
  vtkNew<vtkRenderWindow> renWin;
  renWin->AddRenderer(ren1);
  vtkNew<vtkRenderWindowInteractor> iren;
  iren->SetRenderWindow(renWin);

  ren1->AddActor(polyDataActor);

  ren1->SetBackground(0.1, 0.2, 0.4);
  renWin->SetSize(200, 200);

  ren1->ResetCamera();
  ren1->GetActiveCamera()->Zoom(1.5);
  renWin->Render();

  // This starts the event loop and as a side effect causes an initial render.
  iren->Start();

  return 0;
}

