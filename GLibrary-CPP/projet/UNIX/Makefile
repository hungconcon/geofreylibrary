
PATH_SRC	=	../../sources/
PATH_OBJ	=	../../objects/
FLAGS		=	-W -Wall
PATH_INCLUDE	=	/usr/include/G/
PATH_LIB	=	/usr/lib/
LIB_NAME	=	GLibrary


all:	
	@rm -R $(PATH_OBJ)
	@mkdir $(PATH_OBJ)
	@echo "#######################################"
	@echo "#                                     #"
	@echo "# Debut de la compilation....         #"
	@echo "#                                     #"
	@echo "#######################################"
	@echo "# =====> G - Chaine                   #"
	@echo "# GChar........................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GChar.o 		-c $(PATH_SRC)GChar.cpp
	@echo "# GString......................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GString.o 		-c $(PATH_SRC)GString.cpp
	@echo "# GBase........................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GBase.o 		-c $(PATH_SRC)GBase.cpp
	@echo "# GRegExp......................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GRegExp.o 		-c $(PATH_SRC)GRegExp.cpp
	@echo "# GRegExpOpt...................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GRegExpOpt.o	-c $(PATH_SRC)GRegExpOpt.cpp
	@echo "# GStr............................ OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GStr.o 		-c $(PATH_SRC)GStr.cpp
	@echo "# GCriptography................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GCriptography.o 	-c $(PATH_SRC)GCryptography.cpp
	@echo "#                                     #"
	@echo "# =====> G - Date & Time              #"
	@echo "# GTime........................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GTime.o 		-c $(PATH_SRC)GTime.cpp
	@echo "# GDate........................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GDate.o 		-c $(PATH_SRC)GDate.cpp
	@echo "# GDateTime....................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GDateTime.o 	-c $(PATH_SRC)GDateTime.cpp
	@echo "# GDayInstance.................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GDayInstance.o 	-c $(PATH_SRC)GDayInstance.cpp
	@echo "# GMonthInstance.................. OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GMonthInstance.o 	-c $(PATH_SRC)GMonthInstance.cpp
	@echo "# GPrecisionTime.................. OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GPrecisionTime.o 	-c $(PATH_SRC)GPrecisionTime.cpp
	@echo "# GExecutionTime.................. OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GExecutionTime.o 	-c $(PATH_SRC)GExecutionTime.cpp
	@echo "# GTimeOfDay...................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GTimeOfDay.o 	-c $(PATH_SRC)GTimeOfDay.cpp
	@echo "# GDate (French Day).............. OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)FrenchDay.o 	-c $(PATH_SRC)FrenchDay.cpp
	@echo "# GDate (French Month)............ OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)FrenchMonth.o 	-c $(PATH_SRC)FrenchMonth.cpp
	@echo "# GDate (English Day)............. OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)EnglishDay.o 	-c $(PATH_SRC)EnglishDay.cpp
	@echo "# GDate (English Month)........... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)EnglishMonth.o 	-c $(PATH_SRC)EnglishMonth.cpp
	@echo "#                                     #"
	@echo "# =====> G - DLL                      #"
	@echo "# GLoadLibrary.................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GLoadLibrary.o 	-c $(PATH_SRC)GLoadLibrary.cpp
	@echo "#                                     #"
	@echo "# =====> G - Files & Directories      #"
	@echo "# GDirectory...................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GDirectory.o 	-c $(PATH_SRC)GDirectory.cpp
	@echo "# GFile........................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GFile.o 		-c $(PATH_SRC)GFile.cpp
	@echo "# GFileInfos...................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GFileInfos.o	-c $(PATH_SRC)GFileInfos.cpp
	@echo "#                                     #"
	@echo "# =====> G - Images                   #"
	@echo "# GImage.......................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GImage.o 		-c $(PATH_SRC)GImage.cpp
	@echo "#                                     #"
	@echo "# =====> G - Network                  #"
	@echo "# GSocketTcpClient................ OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GSocketTcpClient.o 	-c $(PATH_SRC)GSocketTcpClient.cpp
	@echo "# GSocketTcpServer................ OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GSocketTcpServer.o 	-c $(PATH_SRC)GSocketTcpServer.cpp
	@echo "# GHttp........................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GHttp.o	 	-c $(PATH_SRC)GHttp.cpp
	@echo "# GSmtp........................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GSmtp.o	 	-c $(PATH_SRC)GSmtp.cpp
	@echo "# GSqlDatabse..................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GSqlDatabase.o	-c $(PATH_SRC)GSqlDatabase.cpp
	@echo "#                                     #"
	@echo "# =====> G - Thread, Mutex & IPC      #"
	@echo "# GIPC............................ OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GIPC.o           	-c $(PATH_SRC)GIPC.cpp
	@echo "# GThread......................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GThread.o 		-c $(PATH_SRC)GThread.cpp
	@echo "# GMutex.......................... OK #"	
	@g++ $(FLAGS) -o $(PATH_OBJ)GMutex.o 		-c $(PATH_SRC)GMutex.cpp
	@echo "# GSleep.......................... OK #"	
	@g++ $(FLAGS) -o $(PATH_OBJ)GSleep.o 		-c $(PATH_SRC)GSleep.cpp
	@echo "#                                     #"
	@echo "# =====> G - System                   #"
	@echo "# GDesktop........................ OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GDesktop.o 		-c $(PATH_SRC)GDesktop.cpp
	@echo "# GMouse.......................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GMouse.o 		-c $(PATH_SRC)GMouse.cpp
	@echo "# GProcessus...................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GProcessus.o 	-c $(PATH_SRC)GProcessus.cpp
	@echo "# GSystem......................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GSystem.o 		-c $(PATH_SRC)GSystem.cpp
	@echo "# GLoadLibrary.................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GLoadLibrary.o	-c $(PATH_SRC)GLoadLibrary.cpp
	@echo "#                                     #"
	@echo "# =====> Warning & Exception          #"
	@echo "# GException...................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GException.o 	-c $(PATH_SRC)GException.cpp
	@echo "# GWarning........................ OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GWarning.o 		-c $(PATH_SRC)GWarning.cpp
	@echo "# G2dPoint........................ OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)G2dPoint.o 		-c $(PATH_SRC)G2dPoint.cpp
	@echo "# G3dPoint........................ OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)G3dPoint.o 		-c $(PATH_SRC)G3dPoint.cpp
	@echo "# GComplexe....................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GComplexe.o 	-c $(PATH_SRC)GComplexe.cpp
	@echo "# GFraction....................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GFraction.o 	-c $(PATH_SRC)GFraction.cpp
	@echo "# GAlgo........................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GAlgo.o 		-c $(PATH_SRC)GAlgo.cpp
	@echo "#                                     #"
	@echo "# =====> Parser                       #"
	@echo "# GXmlWriter...................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GXmlWriter.o 	-c $(PATH_SRC)GXmlWriter.cpp
	@echo "# GXmlReader...................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GXmlReader.o 	-c $(PATH_SRC)GXmlReader.cpp
	@echo "# GHuffman........................ OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GHuffman.o		-c $(PATH_SRC)GHuffman.cpp
	@echo "#                                     #"
	@echo "# =====> GUI                          #"
	@echo "# GApplication.................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GApplication.o 	-c $(PATH_SRC)GApplication.cpp
	@echo "# GSize........................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GSize.o 		-c $(PATH_SRC)GSize.cpp
	@echo "# GMainWindow..................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GMainWindows.o	-c $(PATH_SRC)GMainWindow.cpp
	@echo "# GWidget......................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GWidget.o		-c $(PATH_SRC)GWidget.cpp
	@echo "# GPushButton..................... OK #"
	@g++ $(FLAGS) -o $(PATH_OBJ)GPushButton.o	-c $(PATH_SRC)GPushButton.cpp
	@echo "#######################################"
	@ar r lib$(LIB_NAME).a $(PATH_OBJ)/*.o
	@ranlib lib$(LIB_NAME).a
	@echo "# Creation de $(LIB_NAME).a.......... OK #"
	@rm -Rf $(PATH_INCLUDE)
	@mkdir $(PATH_INCLUDE)
	@cp $(PATH_SRC)*.h $(PATH_INCLUDE)
	@echo "# Copie .h   dans $(PATH_INCLUDE). OK #"
	@cp $(PATH_SRC)*.hpp $(PATH_INCLUDE)
	@echo "# Copie .hpp dans $(PATH_INCLUDE). OK #"
	@cp $(LIB_NAME).a $(PATH_LIB)
	@echo "# Copie $(LIB_NAME).a $(PATH_LIB)...... OK #"
	@echo "#######################################"

re: clean all

clean:
	@rm $(PATH_OBJ)*.o
	@rm -R $(PATH_OBJ)
