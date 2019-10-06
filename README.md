
# OpenCV Project - Ferrilata Rosasite

## Project Members

[Varga Júlia](https://github.com/green-fox-academy/julcsi2121) • [Varga József](https://github.com/green-fox-academy/Joco456) • [Varga Viktor](https://github.com/green-fox-academy/vviktor807) • [Horváth Donát](https://github.com/green-fox-academy/Hordon13)

![](https://i.imgur.com/Pl98F4K.jpg)

## Project goal
The aim of this project is to get familiar with OpenCV in C++. Through the implemented functions, you will see how could we reach from zero to be able to detect, analyze and handle speed limit signs from picture or real environment. 


## Functions

#### Basic Image Processing

* #### Arithmetic Image Operation

    * addition

        ​	With this function you can sum 2 images by pixel values. You can use this function by -add     	flag in command line.

    * subtraction

        ​	With this function you can subtract 2 images from each other by pixel values. You can use      	this function by -subtract flag in command line.

    * multiplication by scalar

        ​	With this function you can multiply the pixels of an image by a scalar value. You can use this      	function by -multiplyScalar flag in command line.

    * multiplication by matrix

        ​	With this function you can multiply 2 images by the  values of their pixels . You can use this     	function by -multiplyMatrix flag in command line.

* #### Wave effect

    ​	With this function you can apply wave effect on images . You can use this function by -wave flag     	in command line.

    ​![](https://i.imgur.com/ZuIprME.jpg)


* #### Image sharpening
         
    ​	With this function you can sharpen images . You can use this function by -sharpen flag in    	      	command line.
          
* #### Salt effect

    ​	With this function you can apply salt effect on images . You can use this function by -salty flag in       	command line.	

    ​	![](https://i.imgur.com/cPZ1IT6.jpg)

           

* #### Reduce Color

    ​   With this function you can reduce the color values of images with trackbar. You can use this function by -reduceColor flag in command line.	

* #### Detect Edges

    ​   With this function you can extract edges of images with trackbar by applying Canny Edge Detection. You can use this function by -edges flag in command line.

    ​	![](https://i.imgur.com/ZgzGHqm.jpg)

           

* #### Image Morphology

    * erode

        With this function you can make lines in images thinner by compute the local minimum over the area of kerner. You can use this function by -erode flag in command line.

        ​	![](https://i.imgur.com/QpxrMAh.jpg)

                

    * dilate

        With this function you can make lines in images thicker by convoluting the image with some kerner. You can use this function by -dilate flag in command line.

        ​	![](https://i.imgur.com/UsoNSRi.jpg)

                

    * open

        With this function you can remove backround noise from images. This is basically an erosion followed by dilation. You can use this function by -open flag in command line.

    * close

        With this function you can remove noise from foreground objects in images. This is the reverse of opening, dilation followed by erosion. You can use this function by -close flag in command line.

* #### Image Geometry

    ​	With this function you can resize and / or rotate images with trackbar. You can use this function 	by -resizeAndRotate flag in command line.

* #### Histogram

    ​	With this function you can see the histogram of a 3 channel image. You can change brightness 	      	and / or contrast with trackbars. You can use this function by -histogram flag in command line.

![](https://media.giphy.com/media/dVi2gWmN9GLyKFMtWG/giphy.gif)

           

* #### Panorama

    ​	With this function you can make panorama pictures by merging images. You can use this function 	by -panorama flag in command line.

* #### Detect Corners

    ​	With this function you can detect corners on images by utilizing a Harris Corner Detection 	   	   	Algorithm. You can use this function by -corners flag in command line.

* #### Decolor

    ​	With this function you can decolor images while using contrast preservation. You can use this 	    	function by -decolorflag in command line.

* #### Separate Colors
      
    ​	With this function you can separate the RGB channels of images. You can use this function by -  	separateColor flag in command line.
      
    ​	![](https://i.imgur.com/rZxx4RY.jpg)
      
           
      
* #### Cartoon Effect
      
    ​	With this function you can apply cartoon effect on images by using color reduction and edge 	 	 detection. You can use this function by -cartoon flag in command line.
        
    ​	![](https://i.imgur.com/apY6ly3.jpg)
      
      
      
#### Advanced Image Processing
    
* #### Detect Circles
          
    ​	With this function you can detect circles on images. You can use this function by -circles flag in   	command line.
            
    ​	![](https://i.imgur.com/zppVvpP.jpg)
            
* #### Detect Text
      
    ​	With this function you can detect text boxes on images by using a pretrained convolutional 	     	neural network. You can use this function by -detectText flag in command line.
      
* #### Read Text
      
    ​	With this function you can read text from a preprocessed image with the help of Tesseract. You      	can use this function by -readText flag in command line.
           
      
#### Advanced Video Processing

* #### Read Speed Limit Sign From Camera Input

    * Modes:

        * Live

            With this mode with the help of a camera input you can detect speed limit signs. You can use this function by -live flag in command line. You can initialize a serial communication by giving a connected device's port name as a value to the flag (-live="portName"). 

        * Setup

            With this mode with the help of a camera input and trackbars you can set the ideal parameters to detect speed limit signs and save it into a database. You can use this function by -setup flag in command line and if you give value to the flag (-setup="presetName") the parameters will be saved by the given name. Otherwise it will be saved with the name "undefined".

        * Load Presets

            With this mode  you can load predefined parameter set from the database via it's name. After a successful call from database the saved parameters will be set and the speed limit sign detection will start. You can use this function by -parameters="presetName" flag in command line.
                    
            ![](https://media.giphy.com/media/L2UEeqkRpZXohXamw7/giphy.gif)
                 
                    

* #### Implemented sorting algorithms

     * Bubble sort
     * Merge sort
     * Heap sort
     * Shell sort
     * Insertion sort
     * Quick sort
     * Selection sort

## Technologies We Used

* C++
* OpenCV
* Jira
* SQL