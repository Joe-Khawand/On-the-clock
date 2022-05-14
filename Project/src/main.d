src/main.o: src/main.cpp ../library/cgp/cgp.hpp \
  ../library/cgp/base/base.hpp ../library/cgp/base/error/error.hpp \
  ../library/cgp/base/basic_types/basic_types.hpp \
  ../library/cgp/base/stl/stl.hpp \
  ../library/cgp/base/stl/../basic_types/basic_types.hpp \
  ../library/cgp/base/types/types.hpp \
  ../library/cgp/base/types/../stl/stl.hpp \
  ../library/cgp/base/string/string.hpp \
  ../library/cgp/base/string/../basic_types/basic_types.hpp \
  ../library/cgp/base/rand/rand.hpp \
  ../library/cgp/containers/containers.hpp \
  ../library/cgp/containers/offset_grid/offset_grid.hpp \
  ../library/cgp/containers/buffer_stack/buffer_stack.hpp \
  ../library/cgp/containers/buffer_stack/implementation/buffer_stack.hpp \
  ../library/cgp/containers/buffer_stack/implementation/buffer_stack2.hpp \
  ../library/cgp/containers/buffer_stack/implementation/buffer_stack3.hpp \
  ../library/cgp/containers/buffer_stack/implementation/buffer_stack4.hpp \
  ../library/cgp/containers/buffer_stack/special_types/special_types.hpp \
  ../library/cgp/containers/buffer_stack/special_types/../implementation/buffer_stack.hpp \
  ../library/cgp/containers/buffer_stack/special_types/../implementation/buffer_stack2.hpp \
  ../library/cgp/containers/buffer_stack/special_types/../implementation/buffer_stack3.hpp \
  ../library/cgp/containers/buffer_stack/special_types/../implementation/buffer_stack4.hpp \
  ../library/cgp/containers/grid_stack/grid_stack.hpp \
  ../library/cgp/containers/grid_stack/grid_stack_2D/grid_stack_2D.hpp \
  ../library/cgp/containers/grid_stack/grid_stack_2D/../../buffer_stack/buffer_stack.hpp \
  ../library/cgp/containers/grid_stack/grid_stack_2D/../../offset_grid/offset_grid.hpp \
  ../library/cgp/containers/buffer/buffer.hpp \
  ../library/cgp/containers/grid/grid.hpp \
  ../library/cgp/containers/grid/grid_2D/grid_2D.hpp \
  ../library/cgp/containers/grid/grid_2D/../../buffer/buffer.hpp \
  ../library/cgp/containers/grid/grid_2D/../../buffer_stack/buffer_stack.hpp \
  ../library/cgp/containers/grid/grid_3D/grid_3D.hpp \
  ../library/cgp/containers/grid/grid_3D/../../buffer/buffer.hpp \
  ../library/cgp/containers/grid/grid_3D/../../buffer_stack/buffer_stack.hpp \
  ../library/cgp/math/math.hpp ../library/cgp/math/matrix/matrix.hpp \
  ../library/cgp/math/matrix/matrix_stack/matrix_stack.hpp \
  ../library/cgp/math/matrix/matrix_stack/special_types/special_types.hpp \
  ../library/cgp/math/matrix/matrix_stack/special_types/definition/special_types.hpp \
  ../library/cgp/math/matrix/matrix_stack/special_types/definition/../../matrix_stack.hpp \
  ../library/cgp/math/matrix/matrix_stack/special_types/mat4/mat4.hpp \
  ../library/cgp/math/matrix/matrix_stack/special_types/mat4/../../matrix_stack.hpp \
  ../library/cgp/math/vec_mat/vec_mat.hpp \
  ../library/cgp/math/rotation_transform/rotation_transform.hpp \
  ../library/cgp/math/rotation_transform/../quaternion/quaternion.hpp \
  ../library/cgp/math/rotation_transform/../matrix/matrix.hpp \
  ../library/cgp/math/quaternion/quaternion.hpp \
  ../library/cgp/math/affine/affine.hpp \
  ../library/cgp/math/affine/affine_rt/affine_rt.hpp \
  ../library/cgp/math/affine/affine_rts/affine_rts.hpp \
  ../library/cgp/math/frame/frame.hpp \
  ../library/cgp/math/projection/projection.hpp \
  ../library/cgp/math/interpolation/interpolation.hpp \
  ../library/cgp/files/files.hpp ../library/cgp/shape/shape.hpp \
  ../library/cgp/shape/mesh/mesh.hpp \
  ../library/cgp/shape/mesh/structure/mesh.hpp \
  ../library/cgp/shape/mesh/primitive/mesh_primitive.hpp \
  ../library/cgp/shape/mesh/primitive/../structure/mesh.hpp \
  ../library/cgp/shape/mesh/loader/loader.hpp \
  ../library/cgp/shape/mesh/loader/obj/obj.hpp \
  ../library/cgp/shape/mesh/loader/obj/../../structure/mesh.hpp \
  ../library/cgp/shape/curve/curve.hpp \
  ../library/cgp/shape/noise/noise.hpp \
  ../library/cgp/shape/intersection/intersection.hpp \
  ../library/cgp/shape/implicit/implicit.hpp \
  ../library/cgp/shape/implicit/marching_cube/marching_cube.hpp \
  ../library/cgp/shape/spatial_domain/spatial_domain.hpp \
  ../library/cgp/shape/spatial_domain/spatial_domain_grid_3D/spatial_domain_grid_3D.hpp \
  ../library/cgp/display/display.hpp \
  ../library/cgp/display/opengl/opengl.hpp \
  ../library/cgp/display/opengl/glad/glad.hpp \
  ../library/third_party/src/glad/include/glad/glad.hpp \
  ../library/cgp/display/opengl/helper/opengl_helper.hpp \
  ../library/cgp/display/opengl/helper/../glad/glad.hpp \
  ../library/cgp/display/opengl/debug/debug.hpp \
  ../library/cgp/display/opengl/debug/../glad/glad.hpp \
  ../library/cgp/display/opengl/uniform/uniform.hpp \
  ../library/cgp/display/opengl/shaders/shaders.hpp \
  ../library/cgp/display/opengl/shaders/../glad/glad.hpp \
  ../library/cgp/display/opengl/texture/texture.hpp \
  ../library/cgp/display/image/image.hpp \
  ../library/cgp/display/window/window.hpp \
  /usr/local/include/GLFW/glfw3.h \
  ../library/cgp/display/drawable/drawable.hpp \
  ../library/cgp/display/drawable/shading_parameters/shading_parameters.hpp \
  ../library/cgp/display/drawable/mesh_drawable/mesh_drawable.hpp \
  ../library/cgp/display/drawable/mesh_wireframe_drawable/mesh_wireframe_drawable.hpp \
  ../library/cgp/display/drawable/mesh_normal_drawable/mesh_normal_drawable.hpp \
  ../library/cgp/display/drawable/curve_drawable/curve_drawable.hpp \
  ../library/cgp/display/drawable/curve_dynamic_drawable/curve_dynamic_drawable.hpp \
  ../library/cgp/display/drawable/curve_dynamic_drawable/../curve_drawable/curve_drawable.hpp \
  ../library/cgp/display/drawable/segments_drawable/segments_drawable.hpp \
  ../library/cgp/display/drawable/trajectory_drawable/trajectory_drawable.hpp \
  ../library/cgp/display/drawable/hierarchy_mesh_drawable/hierarchy_mesh_drawable.hpp \
  ../library/cgp/display/drawable/hierarchy_mesh_drawable/hierarchy_mesh_drawable_node/hierarchy_mesh_drawable_node.hpp \
  ../library/cgp/display/drawable/spatial_domain_grid_drawable/spatial_domain_grid_drawable.hpp \
  ../library/cgp/display/drawable/spatial_domain_grid_drawable/../segments_drawable/segments_drawable.hpp \
  ../library/cgp/display/drawable/triangle_soup_drawable/triangle_soup_drawable.hpp \
  ../library/cgp/display/drawable/triangle_soup_drawable/../shading_parameters/shading_parameters.hpp \
  ../library/cgp/display/drawable/skybox_drawable/skybox_drawable.hpp \
  ../library/cgp/display/drawable/skybox_drawable/../mesh_drawable/mesh_drawable.hpp \
  ../library/cgp/interaction/interaction.hpp \
  ../library/cgp/interaction/camera/camera.hpp \
  ../library/cgp/interaction/camera/camera_base/camera_base.hpp \
  ../library/cgp/interaction/camera/common_functions/common_functions.hpp \
  ../library/cgp/interaction/camera/camera_around_center/camera_around_center.hpp \
  ../library/cgp/interaction/camera/camera_spherical_coordinates/camera_spherical_coordinates.hpp \
  ../library/cgp/interaction/camera/camera_head/camera_head.hpp \
  ../library/cgp/interaction/camera/camera_projection/camera_projection.hpp \
  ../library/cgp/interaction/glfw_inputs/glfw_inputs.hpp \
  ../library/cgp/interaction/gui/gui.hpp \
  ../library/third_party/src/imgui/imgui.h \
  ../library/third_party/src/imgui/imconfig.h \
  ../library/third_party/src/imgui/imgui_impl_glfw.h \
  ../library/third_party/src/imgui/imgui_impl_opengl3.h \
  ../library/cgp/interaction/timer/timer.hpp \
  ../library/cgp/interaction/timer/timer_basic/timer_basic.hpp \
  ../library/cgp/interaction/timer/timer_event_periodic/timer_event_periodic.hpp \
  ../library/cgp/interaction/timer/timer_event_periodic/../timer_basic/timer_basic.hpp \
  ../library/cgp/interaction/timer/timer_fps/timer_fps.hpp \
  ../library/cgp/interaction/timer/timer_fps/../timer_event_periodic/timer_event_periodic.hpp \
  ../library/cgp/interaction/timer/timer_interval/timer_interval.hpp \
  ../library/cgp/interaction/timer/timer_interval/../timer_basic/timer_basic.hpp \
  ../library/cgp/interaction/tracker/tracker.hpp \
  ../library/cgp/interaction/tracker/velocity_tracker/velocity_tracker.hpp \
  ../library/cgp/interaction/camera_standard_behavior/camera_standard_behavior.hpp \
  ../library/cgp/interaction/picking/picking.hpp \
  ../library/cgp/interaction/picking/picking_structure/picking_structure.hpp \
  ../library/cgp/interaction/picking/picking_spheres/picking_spheres.hpp \
  ../library/cgp/interaction/picking/picking_spheres/../picking_structure/picking_structure.hpp \
  ../library/cgp/interaction/picking/picking_plane/picking_plane.hpp \
  ../library/cgp/interaction/picking/picking_plane/../picking_structure/picking_structure.hpp \
  ../library/cgp/helper_common_scene/helper_common_scene.hpp \
  ../library/cgp/helper_common_scene/helper/helper.hpp \
  ../library/cgp/helper_common_scene/scene_environment_basic/scene_environment_basic.hpp \
  src/scene.hpp

../library/cgp/cgp.hpp:

../library/cgp/base/base.hpp:

../library/cgp/base/error/error.hpp:

../library/cgp/base/basic_types/basic_types.hpp:

../library/cgp/base/stl/stl.hpp:

../library/cgp/base/stl/../basic_types/basic_types.hpp:

../library/cgp/base/types/types.hpp:

../library/cgp/base/types/../stl/stl.hpp:

../library/cgp/base/string/string.hpp:

../library/cgp/base/string/../basic_types/basic_types.hpp:

../library/cgp/base/rand/rand.hpp:

../library/cgp/containers/containers.hpp:

../library/cgp/containers/offset_grid/offset_grid.hpp:

../library/cgp/containers/buffer_stack/buffer_stack.hpp:

../library/cgp/containers/buffer_stack/implementation/buffer_stack.hpp:

../library/cgp/containers/buffer_stack/implementation/buffer_stack2.hpp:

../library/cgp/containers/buffer_stack/implementation/buffer_stack3.hpp:

../library/cgp/containers/buffer_stack/implementation/buffer_stack4.hpp:

../library/cgp/containers/buffer_stack/special_types/special_types.hpp:

../library/cgp/containers/buffer_stack/special_types/../implementation/buffer_stack.hpp:

../library/cgp/containers/buffer_stack/special_types/../implementation/buffer_stack2.hpp:

../library/cgp/containers/buffer_stack/special_types/../implementation/buffer_stack3.hpp:

../library/cgp/containers/buffer_stack/special_types/../implementation/buffer_stack4.hpp:

../library/cgp/containers/grid_stack/grid_stack.hpp:

../library/cgp/containers/grid_stack/grid_stack_2D/grid_stack_2D.hpp:

../library/cgp/containers/grid_stack/grid_stack_2D/../../buffer_stack/buffer_stack.hpp:

../library/cgp/containers/grid_stack/grid_stack_2D/../../offset_grid/offset_grid.hpp:

../library/cgp/containers/buffer/buffer.hpp:

../library/cgp/containers/grid/grid.hpp:

../library/cgp/containers/grid/grid_2D/grid_2D.hpp:

../library/cgp/containers/grid/grid_2D/../../buffer/buffer.hpp:

../library/cgp/containers/grid/grid_2D/../../buffer_stack/buffer_stack.hpp:

../library/cgp/containers/grid/grid_3D/grid_3D.hpp:

../library/cgp/containers/grid/grid_3D/../../buffer/buffer.hpp:

../library/cgp/containers/grid/grid_3D/../../buffer_stack/buffer_stack.hpp:

../library/cgp/math/math.hpp:

../library/cgp/math/matrix/matrix.hpp:

../library/cgp/math/matrix/matrix_stack/matrix_stack.hpp:

../library/cgp/math/matrix/matrix_stack/special_types/special_types.hpp:

../library/cgp/math/matrix/matrix_stack/special_types/definition/special_types.hpp:

../library/cgp/math/matrix/matrix_stack/special_types/definition/../../matrix_stack.hpp:

../library/cgp/math/matrix/matrix_stack/special_types/mat4/mat4.hpp:

../library/cgp/math/matrix/matrix_stack/special_types/mat4/../../matrix_stack.hpp:

../library/cgp/math/vec_mat/vec_mat.hpp:

../library/cgp/math/rotation_transform/rotation_transform.hpp:

../library/cgp/math/rotation_transform/../quaternion/quaternion.hpp:

../library/cgp/math/rotation_transform/../matrix/matrix.hpp:

../library/cgp/math/quaternion/quaternion.hpp:

../library/cgp/math/affine/affine.hpp:

../library/cgp/math/affine/affine_rt/affine_rt.hpp:

../library/cgp/math/affine/affine_rts/affine_rts.hpp:

../library/cgp/math/frame/frame.hpp:

../library/cgp/math/projection/projection.hpp:

../library/cgp/math/interpolation/interpolation.hpp:

../library/cgp/files/files.hpp:

../library/cgp/shape/shape.hpp:

../library/cgp/shape/mesh/mesh.hpp:

../library/cgp/shape/mesh/structure/mesh.hpp:

../library/cgp/shape/mesh/primitive/mesh_primitive.hpp:

../library/cgp/shape/mesh/primitive/../structure/mesh.hpp:

../library/cgp/shape/mesh/loader/loader.hpp:

../library/cgp/shape/mesh/loader/obj/obj.hpp:

../library/cgp/shape/mesh/loader/obj/../../structure/mesh.hpp:

../library/cgp/shape/curve/curve.hpp:

../library/cgp/shape/noise/noise.hpp:

../library/cgp/shape/intersection/intersection.hpp:

../library/cgp/shape/implicit/implicit.hpp:

../library/cgp/shape/implicit/marching_cube/marching_cube.hpp:

../library/cgp/shape/spatial_domain/spatial_domain.hpp:

../library/cgp/shape/spatial_domain/spatial_domain_grid_3D/spatial_domain_grid_3D.hpp:

../library/cgp/display/display.hpp:

../library/cgp/display/opengl/opengl.hpp:

../library/cgp/display/opengl/glad/glad.hpp:

../library/third_party/src/glad/include/glad/glad.hpp:

../library/cgp/display/opengl/helper/opengl_helper.hpp:

../library/cgp/display/opengl/helper/../glad/glad.hpp:

../library/cgp/display/opengl/debug/debug.hpp:

../library/cgp/display/opengl/debug/../glad/glad.hpp:

../library/cgp/display/opengl/uniform/uniform.hpp:

../library/cgp/display/opengl/shaders/shaders.hpp:

../library/cgp/display/opengl/shaders/../glad/glad.hpp:

../library/cgp/display/opengl/texture/texture.hpp:

../library/cgp/display/image/image.hpp:

../library/cgp/display/window/window.hpp:

/usr/local/include/GLFW/glfw3.h:

../library/cgp/display/drawable/drawable.hpp:

../library/cgp/display/drawable/shading_parameters/shading_parameters.hpp:

../library/cgp/display/drawable/mesh_drawable/mesh_drawable.hpp:

../library/cgp/display/drawable/mesh_wireframe_drawable/mesh_wireframe_drawable.hpp:

../library/cgp/display/drawable/mesh_normal_drawable/mesh_normal_drawable.hpp:

../library/cgp/display/drawable/curve_drawable/curve_drawable.hpp:

../library/cgp/display/drawable/curve_dynamic_drawable/curve_dynamic_drawable.hpp:

../library/cgp/display/drawable/curve_dynamic_drawable/../curve_drawable/curve_drawable.hpp:

../library/cgp/display/drawable/segments_drawable/segments_drawable.hpp:

../library/cgp/display/drawable/trajectory_drawable/trajectory_drawable.hpp:

../library/cgp/display/drawable/hierarchy_mesh_drawable/hierarchy_mesh_drawable.hpp:

../library/cgp/display/drawable/hierarchy_mesh_drawable/hierarchy_mesh_drawable_node/hierarchy_mesh_drawable_node.hpp:

../library/cgp/display/drawable/spatial_domain_grid_drawable/spatial_domain_grid_drawable.hpp:

../library/cgp/display/drawable/spatial_domain_grid_drawable/../segments_drawable/segments_drawable.hpp:

../library/cgp/display/drawable/triangle_soup_drawable/triangle_soup_drawable.hpp:

../library/cgp/display/drawable/triangle_soup_drawable/../shading_parameters/shading_parameters.hpp:

../library/cgp/display/drawable/skybox_drawable/skybox_drawable.hpp:

../library/cgp/display/drawable/skybox_drawable/../mesh_drawable/mesh_drawable.hpp:

../library/cgp/interaction/interaction.hpp:

../library/cgp/interaction/camera/camera.hpp:

../library/cgp/interaction/camera/camera_base/camera_base.hpp:

../library/cgp/interaction/camera/common_functions/common_functions.hpp:

../library/cgp/interaction/camera/camera_around_center/camera_around_center.hpp:

../library/cgp/interaction/camera/camera_spherical_coordinates/camera_spherical_coordinates.hpp:

../library/cgp/interaction/camera/camera_head/camera_head.hpp:

../library/cgp/interaction/camera/camera_projection/camera_projection.hpp:

../library/cgp/interaction/glfw_inputs/glfw_inputs.hpp:

../library/cgp/interaction/gui/gui.hpp:

../library/third_party/src/imgui/imgui.h:

../library/third_party/src/imgui/imconfig.h:

../library/third_party/src/imgui/imgui_impl_glfw.h:

../library/third_party/src/imgui/imgui_impl_opengl3.h:

../library/cgp/interaction/timer/timer.hpp:

../library/cgp/interaction/timer/timer_basic/timer_basic.hpp:

../library/cgp/interaction/timer/timer_event_periodic/timer_event_periodic.hpp:

../library/cgp/interaction/timer/timer_event_periodic/../timer_basic/timer_basic.hpp:

../library/cgp/interaction/timer/timer_fps/timer_fps.hpp:

../library/cgp/interaction/timer/timer_fps/../timer_event_periodic/timer_event_periodic.hpp:

../library/cgp/interaction/timer/timer_interval/timer_interval.hpp:

../library/cgp/interaction/timer/timer_interval/../timer_basic/timer_basic.hpp:

../library/cgp/interaction/tracker/tracker.hpp:

../library/cgp/interaction/tracker/velocity_tracker/velocity_tracker.hpp:

../library/cgp/interaction/camera_standard_behavior/camera_standard_behavior.hpp:

../library/cgp/interaction/picking/picking.hpp:

../library/cgp/interaction/picking/picking_structure/picking_structure.hpp:

../library/cgp/interaction/picking/picking_spheres/picking_spheres.hpp:

../library/cgp/interaction/picking/picking_spheres/../picking_structure/picking_structure.hpp:

../library/cgp/interaction/picking/picking_plane/picking_plane.hpp:

../library/cgp/interaction/picking/picking_plane/../picking_structure/picking_structure.hpp:

../library/cgp/helper_common_scene/helper_common_scene.hpp:

../library/cgp/helper_common_scene/helper/helper.hpp:

../library/cgp/helper_common_scene/scene_environment_basic/scene_environment_basic.hpp:

src/scene.hpp:
