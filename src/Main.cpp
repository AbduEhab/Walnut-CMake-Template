#include "Constants.h"

#ifdef _WIN32

#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"

class ExampleLayer : public Walnut::Layer
{
public:
	virtual void OnUIRender() override // Called every frame
	{
		PROFILE_FUNCTION();

		ImGui::Begin("Hello");
		ImGui::Button("Button");
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
};

Walnut::Application *Walnut::CreateApplication([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
	Instrumentor::Get().beginSession("Main func"); // Start profiling session

	Walnut::ApplicationSpecification spec; // Create application specification
	spec.Name = "Walnut Example";		   // Set the name of the application

	Walnut::Application *app = new Walnut::Application(spec); // Create the application
	app->PushLayer<ExampleLayer>();							  // Push the layer to the application
	app->SetMenubarCallback([app]()
							{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		} });
	return app;
}

#else

int main(int, char **)
{
	print("GNU/Linux is not yet supported (but i'm looking into it).\n");
}

#endif
