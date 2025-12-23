#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

/**
 * Bu uygulama Linux (Fedora/GNOME) üzerinde en yüksek performansı sağlamak için 
 * GTK3 ve WebKitGTK kütüphanelerini kullanarak geliştirilmiştir.
 */

// Harici bağlantıları sistemin varsayılan tarayıcısında açmak için kullanılan fonksiyon
static gboolean decide_policy_cb(WebKitWebView *web_view,
                                WebKitPolicyDecision *decision,
                                WebKitPolicyDecisionType type,
                                gpointer user_data) {
    if (type == WEBKIT_POLICY_DECISION_TYPE_NAVIGATION_ACTION) {
        WebKitNavigationPolicyDecision *navigation_decision = WEBKIT_NAVIGATION_POLICY_DECISION(decision);
        WebKitNavigationAction *navigation_action = webkit_navigation_policy_decision_get_navigation_action(navigation_decision);
        WebKitURIRequest *request = webkit_navigation_action_get_request(navigation_action);
        const gchar *uri = webkit_uri_request_get_uri(request);

        // Eğer URI whatsapp.com içermiyorsa, sistemin varsayılan tarayıcısında aç
        // Bu sayede uygulama içinde istenmeyen sekmelerin açılması engellenir.
        if (g_strrstr(uri, "web.whatsapp.com") == NULL && 
            g_strrstr(uri, "whatsapp.net") == NULL) {
            
            g_print("Harici bağlantı algılandı, sistem tarayıcısında açılıyor: %s\n", uri);
            gtk_show_uri_on_window(NULL, uri, GDK_CURRENT_TIME, NULL);
            webkit_policy_decision_ignore(decision);
            return TRUE;
        }
    }
    return FALSE;
}

static void activate(GtkApplication *app, gpointer user_data) {
    // Ana pencereyi oluştur
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "WhatsApp Web");
    gtk_window_set_default_size(GTK_WINDOW(window), 1100, 800);
    
    // Webview ayarlarını yapılandır
    WebKitSettings *settings = webkit_settings_new();
    
    // Fedora üzerinde en iyi uyum için güncel bir User-Agent
    webkit_settings_set_user_agent(settings, "Mozilla/5.0 (X11; Fedora; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36");
    webkit_settings_set_enable_developer_extras(settings, FALSE);
    webkit_settings_set_enable_resizable_text_areas(settings, TRUE);
    webkit_settings_set_enable_javascript(settings, TRUE);

    // WebView (tarayıcı bileşeni) oluştur
    GtkWidget *web_view = webkit_web_view_new_with_settings(settings);
    
    // Pencereye webview'ı ekle
    gtk_container_add(GTK_CONTAINER(window), web_view);

    // Politika kararı sinyalini bağla (bağlantıları kontrol etmek için)
    g_signal_connect(web_view, "decide-policy", G_CALLBACK(decide_policy_cb), NULL);

    // WhatsApp Web'i yükle
    webkit_web_view_load_uri(WEBKIT_WEB_VIEW(web_view), "https://web.whatsapp.com/");

    // Her şeyi görünür yap
    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.whatsapp.desktop.fedora", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}