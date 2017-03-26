LOCAL_PATH := $(call my-dir)

# Build support lib
LOCAL_CFLAGS := -DOS_ANDROID \
				-D_ANDROID
           
LOCAL_MODULE := libsoil
LOCAL_MODULE_FILENAME := libsoil

LOCAL_CFLAGS	:= -mandroid \
					-ffunction-sections \
					-funwind-tables \
					-fstack-protector \
					-fpic \
					-Wno-psabi \
					-Wno-write-strings \
					-fsigned-char \
					-fomit-frame-pointer \
					-fno-strict-aliasing \
					-finline-limit=300 \
					-ffast-math \
					-pipe \
					-g \
					-w -O3 \
					-fno-rtti \
                    -fexceptions
					
LOCAL_SRC_FILES :=	..\..\..\lib\soil\src\image_DXT.c \
					..\..\..\lib\soil\src\image_helper.c \
					..\..\..\lib\soil\src\stb_image_aug.c \
					..\..\..\lib\soil\src\original\stb_image-1.09.c \
					..\..\..\lib\soil\src\original\stb_image-1.16.c		

include $(BUILD_STATIC_LIBRARY)			

LOCAL_CFLAGS := -DOS_ANDROID \
				-D_ANDROID
           
LOCAL_MODULE := libbullet
LOCAL_MODULE_FILENAME := libbullet

LOCAL_CFLAGS	:= -mandroid \
					-ffunction-sections \
					-funwind-tables \
					-fstack-protector \
					-fpic \
					-Wno-psabi \
					-Wno-write-strings \
					-fsigned-char \
					-fomit-frame-pointer \
					-fno-strict-aliasing \
					-finline-limit=300 \
					-ffast-math \
					-pipe \
					-g \
					-w -O3 \
					-fno-rtti \
                    -fexceptions

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../lib/BulletPhysic/src/physicBullet/src \

					
LOCAL_SRC_FILES :=	..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\Featherstone\btMultiBody.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\Featherstone\btMultiBodyConstraint.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\Featherstone\btMultiBodyConstraintSolver.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\Featherstone\btMultiBodyDynamicsWorld.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\Featherstone\btMultiBodyJointLimitConstraint.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\Featherstone\btMultiBodyJointMotor.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\Featherstone\btMultiBodyPoint2Point.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\Dynamics\btDiscreteDynamicsWorld.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\Dynamics\btRigidBody.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\Dynamics\btSimpleDynamicsWorld.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\Character\btKinematicCharacterController.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\MLCPSolvers\btDantzigLCP.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\MLCPSolvers\btLemkeAlgorithm.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\MLCPSolvers\btMLCPSolver.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\Vehicle\btRaycastVehicle.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\Vehicle\btWheelInfo.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\BroadphaseCollision\btAxisSweep3.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\BroadphaseCollision\btBroadphaseProxy.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\BroadphaseCollision\btCollisionAlgorithm.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\BroadphaseCollision\btDbvt.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\BroadphaseCollision\btDbvtBroadphase.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\BroadphaseCollision\btDispatcher.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\BroadphaseCollision\btMultiSapBroadphase.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\BroadphaseCollision\btOverlappingPairCache.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\BroadphaseCollision\btQuantizedBvh.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\BroadphaseCollision\btSimpleBroadphase.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btActivatingCollisionAlgorithm.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btBox2dBox2dCollisionAlgorithm.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btBoxBoxCollisionAlgorithm.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btBoxBoxDetector.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btCollisionDispatcher.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btCollisionObject.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btCollisionWorld.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btCollisionWorldImporter.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btCompoundCollisionAlgorithm.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btCompoundCompoundCollisionAlgorithm.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btConvex2dConvex2dAlgorithm.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btConvexConcaveCollisionAlgorithm.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btConvexConvexAlgorithm.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btConvexPlaneCollisionAlgorithm.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btDefaultCollisionConfiguration.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btEmptyCollisionAlgorithm.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btGhostObject.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btHashedSimplePairCache.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btInternalEdgeUtility.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btManifoldResult.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btSimulationIslandManager.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btSphereBoxCollisionAlgorithm.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btSphereSphereCollisionAlgorithm.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btSphereTriangleCollisionAlgorithm.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\btUnionFind.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionDispatch\SphereTriangleDetector.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btBox2dShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btBoxShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btBvhTriangleMeshShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btCapsuleShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btCollisionShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btCompoundShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btConcaveShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btConeShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btConvex2dShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btConvexHullShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btConvexInternalShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btConvexPointCloudShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btConvexPolyhedron.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btConvexShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btConvexTriangleMeshShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btCylinderShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btEmptyShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btHeightfieldTerrainShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btMinkowskiSumShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btMultimaterialTriangleMeshShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btMultiSphereShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btOptimizedBvh.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btPolyhedralConvexShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btScaledBvhTriangleMeshShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btShapeHull.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btSphereShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btStaticPlaneShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btStridingMeshInterface.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btTetrahedronShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btTriangleBuffer.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btTriangleCallback.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btTriangleIndexVertexArray.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btTriangleIndexVertexMaterialArray.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btTriangleMesh.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btTriangleMeshShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\CollisionShapes\btUniformScalingShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\Gimpact\btContactProcessing.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\Gimpact\btGenericPoolAllocator.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\Gimpact\btGImpactBvh.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\Gimpact\btGImpactCollisionAlgorithm.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\Gimpact\btGImpactQuantizedBvh.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\Gimpact\btGImpactShape.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\Gimpact\btTriangleShapeEx.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\Gimpact\gim_box_set.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\Gimpact\gim_contact.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\Gimpact\gim_memory.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\Gimpact\gim_tri_collision.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\NarrowPhaseCollision\btContinuousConvexCollision.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\NarrowPhaseCollision\btConvexCast.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\NarrowPhaseCollision\btGjkConvexCast.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\NarrowPhaseCollision\btGjkEpa2.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\NarrowPhaseCollision\btGjkEpaPenetrationDepthSolver.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\NarrowPhaseCollision\btGjkPairDetector.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\NarrowPhaseCollision\btMinkowskiPenetrationDepthSolver.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\NarrowPhaseCollision\btPersistentManifold.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\NarrowPhaseCollision\btPolyhedralContactClipping.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\NarrowPhaseCollision\btRaycastCallback.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\NarrowPhaseCollision\btSubSimplexConvexCast.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletCollision\NarrowPhaseCollision\btVoronoiSimplexSolver.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\LinearMath\btAlignedAllocator.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\LinearMath\btConvexHull.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\LinearMath\btConvexHullComputer.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\LinearMath\btGeometryUtil.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\LinearMath\btPolarDecomposition.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\LinearMath\btQuickprof.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\LinearMath\btSerializer.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\LinearMath\btVector3.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\ConstraintSolver\btConeTwistConstraint.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\ConstraintSolver\btContactConstraint.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\ConstraintSolver\btFixedConstraint.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\ConstraintSolver\btGearConstraint.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\ConstraintSolver\btGeneric6DofConstraint.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\ConstraintSolver\btGeneric6DofSpring2Constraint.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\ConstraintSolver\btGeneric6DofSpringConstraint.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\ConstraintSolver\btHinge2Constraint.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\ConstraintSolver\btHingeConstraint.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\ConstraintSolver\btNNCGConstraintSolver.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\ConstraintSolver\btPoint2PointConstraint.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\ConstraintSolver\btSequentialImpulseConstraintSolver.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\ConstraintSolver\btSliderConstraint.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\ConstraintSolver\btSolve2LinearConstraint.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\ConstraintSolver\btTypedConstraint.cpp \
					..\..\..\lib\BulletPhysic\src\physicBullet\src\BulletDynamics\ConstraintSolver\btUniversalConstraint.cpp
				

					
include $(BUILD_STATIC_LIBRARY)		




# Build main lib
include $(CLEAR_VARS)

LOCAL_CFLAGS := -DOS_ANDROID \
				-D_ANDROID \
				-UNDEBUG 
           
LOCAL_MODULE := libtrainingfw
LOCAL_MODULE_FILENAME := libtrainingfw

LOCAL_LDLIBS	:= -llog -lGLESv2 -lEGL -landroid
LOCAL_CFLAGS	:= 	-mandroid \
					-ffunction-sections \
					-funwind-tables \
					-fstack-protector \
					-fpic \
					-Wno-psabi \
					-Wno-write-strings \
					-fsigned-char \
					-fomit-frame-pointer \
					-fno-strict-aliasing \
					-finline-limit=300 \
					-ffast-math \
					-pipe \
					-g \
					-w -O3 \
					-fno-rtti \
                    -fexceptions
					
LOCAL_LDFLAGS	:= -Wl,--allow-multiple-definition

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../source \
					$(LOCAL_PATH)/../../../lib/soil/src \
					$(LOCAL_PATH)/../../../lib/BulletPhysic/src/physicBullet/src \
					
LOCAL_SRC_FILES :=	main.cpp \
					../../../source/Game.cpp \
					../../../source/Platform/InputManager.cpp \
					../../../source/Platform/PlatformAndroid.cpp \
					../../../source/Utils/FPSLimiter.cpp \
					../../../source/Camera.cpp \
					../../../source/Object.cpp \
					../../../source/Object2D.cpp \
					../../../source/ResourceManager.cpp \
					../../../source/SceneManager.cpp \
					../../../source/Menu.cpp \
					../../../source/Video/Texture.cpp \
					../../../source/Video/Program.cpp \
					../../../source/Save.cpp \
					../../../source/WaterCaustic.cpp \
					../../../source/XMath.cpp
					
	
					
LOCAL_WHOLE_STATIC_LIBRARIES := soil bullet

include $(BUILD_SHARED_LIBRARY)
