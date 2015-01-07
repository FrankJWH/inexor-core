#include "cefcontext.h"

CefRefPtr<CefV8Value> InexorCefContext::GetContext() {
    if (!context.get())
    {
        // This has to be happen when the context is initialized
    	InitializeContext();
    }
    return context;
}

void InexorCefContext::InitializeContext() {
    context = CefV8Value::CreateObject(this);

    // Events
    context->SetValue("subscribe", CefV8Value::CreateFunction("subscribe", this), V8_PROPERTY_ATTRIBUTE_NONE);

    // Methods
    context->SetValue("logoutf", CefV8Value::CreateFunction("logoutf", this), V8_PROPERTY_ATTRIBUTE_READONLY);
    context->SetValue("quit", CefV8Value::CreateFunction("quit", this), V8_PROPERTY_ATTRIBUTE_READONLY);

    // Variables
    context->SetValue("curtime", V8_ACCESS_CONTROL_ALL_CAN_READ, V8_PROPERTY_ATTRIBUTE_READONLY);
    context->SetValue("lastmillis", V8_ACCESS_CONTROL_ALL_CAN_READ, V8_PROPERTY_ATTRIBUTE_READONLY);
    context->SetValue("elapsedtime", V8_ACCESS_CONTROL_ALL_CAN_READ, V8_PROPERTY_ATTRIBUTE_READONLY);
    context->SetValue("totalmillis", V8_ACCESS_CONTROL_ALL_CAN_READ, V8_PROPERTY_ATTRIBUTE_READONLY);
    context->SetValue("totalsecs", V8_ACCESS_CONTROL_ALL_CAN_READ, V8_PROPERTY_ATTRIBUTE_READONLY);
    context->SetValue("thirdperson", V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE);
    context->SetValue("fullscreen", V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE);
    context->SetValue("scr_w", V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE);
    context->SetValue("scr_h", V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE);
    context->SetValue("vsync", V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE);
    // Variables Client
    context->SetValue("name", V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE);

}

bool InexorCefContext::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    logoutf("Executing function %s", name.ToString().c_str());
    if (name == "subscribe") {
        if (arguments.size() == 1 && arguments[0]->IsFunction()) {
            /*
            CefRefPtr<CefV8Handler> callback_handler = arguments[0]->GetFunctionHandler();
            CefString function_name = arguments[0]->GetFunctionName();
            CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
            */
            // manage the
            return true;
        }
    } else if (name == "logoutf") {
        logoutf("logoutf lastmillis: %d", lastmillis);
        retval = CefV8Value::CreateUndefined();
        return true;
    } else if (name == "quit") {
    	quit();
    	return true;
    }
    return false;
}

bool InexorCefContext::Get(const CefString& name, const CefRefPtr<CefV8Value> object, CefRefPtr<CefV8Value>& return_value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
logoutf("Get(%s)", name.ToString().c_str());
    if (name == "curtime")
        return_value = CefV8Value::CreateInt(curtime);
    else if (name == "lastmillis")
        return_value = CefV8Value::CreateInt(lastmillis);
    else if (name == "elapsedtime")
        return_value = CefV8Value::CreateInt(elapsedtime);
    else if (name == "totalmillis")
        return_value = CefV8Value::CreateInt(totalmillis);
    else if (name == "totalsecs")
        return_value = CefV8Value::CreateUInt(totalsecs);
    else if (name == "thirdperson")
        return_value = CefV8Value::CreateInt(thirdperson);
    else if (name == "fullscreen")
        return_value = CefV8Value::CreateInt(fullscreen);
    else if (name == "scr_w")
        return_value = CefV8Value::CreateInt(scr_w);
    else if (name == "scr_h")
        return_value = CefV8Value::CreateInt(scr_h);
    else if (name == "vsync")
        return_value = CefV8Value::CreateInt(vsync);
    else if (name == "name")
        return_value = CefV8Value::CreateString(game::player1->name);
    else
        return false;
    return true;
}

bool InexorCefContext::Set(const CefString& name, const CefRefPtr<CefV8Value> object, const CefRefPtr<CefV8Value> value, CefString& exception)
{
    CEF_REQUIRE_RENDERER_THREAD();
    logoutf("Set(%s)", name.ToString().c_str());
    if (value->IsInt()) {
        if (name == "thirdperson")
            thirdperson = value->GetIntValue();
        else if (name == "fullscreen")
            fullscreen = value->GetIntValue();
        else if (name == "scr_h")
            scr_h = value->GetIntValue();
        else if (name == "scr_h")
            scr_h = value->GetIntValue();
        else if (name == "vsync")
            vsync = value->GetIntValue();
        else if (name == "name")
            game::switchname(value->GetStringValue().ToString().c_str());
        else
            return false;
        return true;
    }
   	return false;
}