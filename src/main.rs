use tao::{
    event::{Event, WindowEvent},
    event_loop::{ControlFlow, EventLoop},
    window::WindowBuilder,
};

use wry::webview::WebViewBuilder;

fn main() -> wry::Result<()> {
    std::env::set_var("GDK_BACKEND", "wayland,x11");
    std::env::set_var("WEBKIT_DISABLE_COMPOSITING_MODE", "1");
    std::env::set_var("WEBKIT_FORCE_SANDBOX", "0");

    let event_loop = EventLoop::new();

    let window = WindowBuilder::new()
        .with_title("WhatsApp")
        .with_inner_size(tao::dpi::LogicalSize::new(1000.0, 700.0))
        .with_resizable(true)
        .with_min_inner_size(tao::dpi::LogicalSize::new(640.0, 480.0))
        .build(&event_loop)
        .expect("Pencere oluşturulamadı");

    let _webview = WebViewBuilder::new(window)?
        .with_url("https://web.whatsapp.com")?
        .build()?;

    event_loop.run(move |event, _, control_flow| {
        *control_flow = ControlFlow::Wait;

        if let Event::WindowEvent {
            event: WindowEvent::CloseRequested,
            ..
        } = event
        {
            *control_flow = ControlFlow::Exit;
        }
    });
}
