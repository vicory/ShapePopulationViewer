#ifndef SHAPEPOPULATIONVIEWER_H
#define SHAPEPOPULATIONVIEWER_H

// local
#include "ui_ShapePopulationViewer.h"

// Basics
#include <vtkSmartPointer.h>
#include <sstream>

// PolyData
#include <vtkPolyDataReader.h>
#include <vtkPolyDataWriter.h>
#include <vtkPolyData.h>
#include <vtkPolyDataNormals.h>

// Visualization
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindow.h>
#include <vtkCamera.h>
#include <QVTKWidget.h>

// Scalars
#include <vtkPointData.h>
#include <vtkFloatArray.h>
//#include <vtkDataArray.h>
//#include <vtkScalarsToColors.h>

// Transfer Function
#include <vtkColorTransferFunction.h>
#include <vtkLookupTable.h>
#include <vtkScalarBarActor.h>

// Window Annotations
#include <vtkCornerAnnotation.h>
#include <vtkTextProperty.h>

// QT
#include <QFileDialog>
#include <QKeyEvent>
#include <QKeySequence>
#include <QDebug>


/**
 * ShapePopulationViewer Gui class specification.  This class contains all model data and controller callbacks, if we are going to consider the code within the MVC paradigm.  See
 * ui_ShapePopulationViewer.h for information on the construction of the gui itself.  It is an autogenerated file from the ShapePopulationViewer.ui file, which could also be used as reference.
 *
 * Generally speaking there are two classes of functionality given by the code, viewing options and filesystem interaction.  The filesystem interaction is supported by callbacks which an both read and write meshes to .vtk
 * formatted files.  The viewing option functionality includes the propogation of renderer interaction between QVTKWidgets, the ability to rearrange the QVTKWidgets in a user specified number of columns, and the ability to
 * change the colormap used to view the meshes, ranging over any colormap present in the .vtk file originally.
 *
 * @brief The ShapePopulationViewer class
 * @author Michael Guarino
 */
class ShapePopulationViewer : public QMainWindow, public Ui::ShapePopulationViewer
{
  Q_OBJECT

public:

    ShapePopulationViewer();
  ~ShapePopulationViewer() {} //TO DO : Desallocate pointers

public slots:

  virtual void slotExit();

protected:

    /**
    * The user selected files
    * @brief meshesList
    */
    QFileInfoList meshesList;
   /**
    * vtkcamera shared by the renderWindows when the surfaces are synchronized
    * @brief headcam
    */
   vtkCamera *headcam;
   /**
    * vector of QVTKWidget
    * @brief widgetList
    */
   QVector<QVTKWidget *> *widgetList;
   /**
    * Vector of vtkRenderWindows selected
    * @brief windowList
    */
   QVector<vtkRenderWindow *> *windowList;


   //DISPLAY
   void updateWidgets();
   void SelectedWidget(vtkObject* selectedObject, unsigned long, void*);
   void UnselectWidget(vtkObject*, unsigned long, void* voidEvent);
   void ModifiedHandler();

   //COLORMAP
   void updateCMaps(vtkMapper*  mapper, vtkColorTransferFunction* DistanceMapTFunc, double *rangeLUT);

   //PLACING WIDGETS
   void printColNumber(int colNumber);
   int getNumberOfColumns();
   int getNumberOfRows(int colNumber);
   void placeWidgetInArea(int colNumber);
   void resizeWidgetInArea();
   void resizeEvent(QResizeEvent* event);

protected slots:

   //MENU
   void writeMeshes();
   void openDirectory();
   void openFiles();
   void closeAll();

   //VIEW
   void on_radioButton_4_toggled();  //all
   void on_radioButton_5_toggled(); //square
   void on_colNumberEdit_editingFinished();
   void on_colNumberSlider_valueChanged();
   void on_colNumberSlider_sliderReleased();

   //SYNCHRONIZATION
   void on_radioButton_1_toggled();
   void on_radioButton_2_toggled();
   void on_checkBox_synchro_toggled(bool checked);

   //COLORMAP
   void on_pushButton_flip_clicked();
   void on_colorMapBox_currentIndexChanged();

   //AXIS
   void viewChange(int x, int y, int z);
   void on_toolButton_0_clicked();
   void on_toolButton_1_clicked();
   void on_toolButton_2_clicked();
   void on_toolButton_3_clicked();
   void on_toolButton_4_clicked();
   void on_toolButton_5_clicked();
   void on_toolButton_6_clicked();

};

#endif
