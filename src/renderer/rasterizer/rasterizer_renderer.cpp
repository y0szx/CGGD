#include "rasterizer_renderer.h"

#include "utils/resource_utils.h"


void cg::renderer::rasterization_renderer::init()
{
	rasterizer = std::make_shared<cg::renderer::rasterizer<cg::vertex, cg::unsigned_color>>();
	rasterizer->set_viewport(settings->width, settings->height);

	render_target = std::make_shared<cg::resource<cg::unsigned_color>>(
			settings->width, settings->height);
	rasterizer->set_render_target(render_target);

	model = std::make_shared<cg::world::model>();
	model->load_obj(settings->model_path);

	// TODO Lab: 1.04 Setup an instance of camera `cg::world::camera` class in `cg::renderer::rasterization_renderer`
	// TODO Lab: 1.06 Add depth buffer in `cg::renderer::rasterization_renderer`
}
void cg::renderer::rasterization_renderer::render()
{
	auto start = std::chrono::high_resolution_clock::now();
	rasterizer->clear_render_target({0, 0, 0});
	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float, std::milli> clear_duration = stop - start;
	std::cout << "Clearing took " << clear_duration.count() << "ms\n";

	for (size_t shape_id = 0; shape_id < model->get_index_buffers().size(); shape_id++)
	{
		rasterizer->set_vertex_buffer(model->get_vertex_buffers()[shape_id]);
		rasterizer->set_index_buffer(model->get_index_buffers()[shape_id]);
		rasterizer->draw(
				model->get_index_buffers()[shape_id]->get_number_of_elements(),
				0);
	}
	stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float, std::milli> rendering_duration = stop - start;
	std::cout << "Rendering took " << rendering_duration.count() << "ms\n";

	cg::utils::save_resource(*render_target, settings->result_path);
	// TODO Lab: 1.04 Implement `vertex_shader` lambda for the instance of `cg::renderer::rasterizer`
	// TODO Lab: 1.05 Implement `pixel_shader` lambda for the instance of `cg::renderer::rasterizer`
}

void cg::renderer::rasterization_renderer::destroy() {}

void cg::renderer::rasterization_renderer::update() {}