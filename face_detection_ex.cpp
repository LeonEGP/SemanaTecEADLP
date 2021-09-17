// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*

    This example program shows how to find frontal human faces in an image.  In
    particular, this program shows how you can take a list of images from the
    command line and display each on the screen with red boxes overlaid on each
    human face.

    The examples/faces folder contains some jpg images of people.  You can run
    this program on them and see the detections by executing the following command:
        ./face_detection_ex faces/*.jpg

    
    This face detector is made using the now classic Histogram of Oriented
    Gradients (HOG) feature combined with a linear classifier, an image pyramid,
    and sliding window detection scheme.  This type of object detector is fairly
    general and capable of detecting many types of semi-rigid objects in
    addition to human faces.  Therefore, if you are interested in making your
    own object detectors then read the fhog_object_detector_ex.cpp example
    program.  It shows how to use the machine learning tools which were used to
    create dlib's face detector. 


    Finally, note that the face detector is fastest when compiled with at least
    SSE2 instructions enabled.  So if you are using a PC with an Intel or AMD
    chip then you should enable at least SSE2 instructions.  If you are using
    cmake to compile this program you can enable them by using one of the
    following commands when you create the build project:
        cmake path_to_dlib_root/examples -DUSE_SSE2_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_SSE4_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_AVX_INSTRUCTIONS=ON
    This will set the appropriate compiler options for GCC, clang, Visual
    Studio, or the Intel compiler.  If you are using another compiler then you
    need to consult your compiler's manual to determine how to enable these
    instructions.  Note that AVX is the fastest but requires a CPU from at least
    2011.  SSE4 is the next fastest and is supported by most current machines.  
*/

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>

using namespace dlib;
using namespace std;

/*
    MODIFICADO POR EL EQUIPO:
    Cada modificación atiende a las dictadas en las diapositivas.
        León García - MOD1
        Jesús Palomino - MOD2
        Alexis Sahagun - MOD
        Diego Martínez - MOD3
*/

// ----------------------------------------------------------------------------------------

int main(int argc, char** argv)
{  
    try
    {
        if (argc == 1)
        {
            cout << "Give some image files as arguments to this program." << endl;
            return 0;
        }

        frontal_face_detector detector = get_frontal_face_detector();
        image_window win;

        // Loop over all the images provided on the command line.
        for (int i = 1; i < argc; ++i)
        {
            //  Imprimir el nombre de la Imagen que se está procesando - MOD1
            cout << "\nProcesando imagen " << argv[i] << endl;
            cout << endl;
            
            //  Array de usigned char para guardar contenido de Imagen a procesar - MOD1
            array2d<unsigned char> img;
            
            //  Array de pixeles de color para mantener la Imagen a color - MOD1
            array2d<rgb_pixel> img_rgb;

            //  Mantener Imagen original, ya que al ser procesada es cambiada a blanco y negro - MOD1
            load_image(img, argv[i]);
            load_image(img_rgb, argv[i]);

            // Make the image bigger by a factor of two.  This is useful since
            // the face detector looks for faces that are about 80 by 80 pixels
            // or larger.  Therefore, if you want to find faces that are smaller
            // than that then you need to upsample the image as we do here by
            // calling pyramid_up().  So this will allow it to detect faces that
            // are at least 40 by 40 pixels in size.  We could call pyramid_up()
            // again to find even smaller faces, but note that every time we
            // upsample the image we make the detector run slower since it must
            // process a larger image.
            
            pyramid_up(img);
            pyramid_up(img_rgb);

            // Now tell the face detector to give us a list of bounding boxes
            // around all the faces it can find in the image.
            
            std::vector<rectangle> dets = detector(img);
            
            // Imprimir coordenadas de limites en ejes x y y de bordes en donde se detectaron caras - MOD2
            int j = 1;
            
            // Pasar por cada rectangle dentro de dets - MOD2
            for (rectangle rec : dets)
            {
                //  Numero de cara detectada - MOD2
                cout << "Cara " << j << " detectada: ";
                
                // Output de coordenada con su lado correspondiente -MOD2
                cout << "Top: " << rec.top() << "\tLeft: " << rec.left() << "\tBottom: " << rec.bottom() << "\tRight: " << rec.right() << endl;
                
                j++;
            }

           // Imprimir el numero total de caras detectadas - MOD3
            cout << "Number of faces detected: " << dets.size() << endl;
            
            // Now we show the image on the screen and the face detections as
            // red overlay boxes.
            
            win.clear_overlay();
            
            // Set de Imagen original para mantener color - MOD1
            
            win.set_image(img_rgb);
            // Set de color a borde a verde - MOD3
            win.add_overlay(dets, rgb_pixel(255,0,0));

            cout << "Hit enter to process the next image..." << endl;
            cin.get();
        }
    }
    catch (exception& e)
    {
        cout << "\nexception thrown!" << endl;
        cout << e.what() << endl;
    }

       //  Agregar conidición para solo imprimir linea si se da más de una imagen como parametro
            //  Condición si no es la ultima imagen a procesar
            if (argc - i != 1)
            {
                // Imprimir linea para diferenciar procesamiento de cada imagen
                for (int z = 0; z < 70; z++)
                {
                    cout << "-";
                }
                // Continuar
                cout << "\nPresiona enter para continuar con la siguiente imagen..." << endl;
            }
            // Ultima imagen
            else   
            {
                // Finalizar
                cout << "Presione enter para finalizar..." << endl;
            }
            cin.get();
        }
    }
    catch (exception& e)
    {
        cout << "\nexception thrown!" << endl;
        cout << e.what() << endl;
    }
}

// ----------------------------------------------------------------------------------------
