EXECUTABLE = FishingJoy

INCLUDES = -I.. -I../Classes

SOURCES = main.cpp \
        ../Classes/AppDelegate.cpp \
        ../Classes/HelloWorldScene.cpp\
	../Classes/Cannon.cpp\
	../Classes/Bullet.cpp\
	../Classes/FishingJoyData.cpp\
	../Classes/StaticData.cpp\
	../Classes/BackgroundLayer.cpp\
	../Classes/FishingNet.cpp\
	../Classes/FishLayer.cpp\
	../Classes/Fish.cpp\
	../Classes/MenuLayer.cpp\
	../Classes/CannonLayer.cpp\
	../Classes/GameScene.cpp\
	../Classes/PanelLayer.cpp\
	../Classes/Weapon.cpp\
	../Classes/TouchLayer.cpp\
	../Classes/PanelLayer.cpp\
	../Classes/Counter.cpp\
	../Classes/GoldCounterLayer.cpp\
	../Classes/PersonalAudioEngine.cpp

COCOS_ROOT = ../../..
include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

SHAREDLIBS += -lcocos2d
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
