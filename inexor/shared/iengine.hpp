#pragma once

// the interface the game uses to access the engine

#include "inexor/rpc/SharedTree.hpp"

#include "inexor/macros/constants.hpp"
#include "inexor/macros/material_macros.hpp"

#include "inexor/enumerations/material_flags.hpp"
#include "inexor/enumerations/material_types.hpp"
#include "inexor/enumerations/ray_types.hpp"
#include "inexor/enumerations/edit_states.hpp"
#include "inexor/enumerations/particle_types.hpp"
#include "inexor/enumerations/decal_types.hpp"
#include "inexor/enumerations/model_rendering_flags.hpp"
#include "inexor/enumerations/disconnect_reasons.hpp"
#include "inexor/enumerations/old_3dgui_modes.hpp"
#include "inexor/enumerations/old_gui_modes.hpp"
#include "inexor/enumerations/edit_states.hpp"

#include "inexor/classes/g3d_gui.hpp"
#include "inexor/classes/g3d_callback.hpp"
#include "inexor/classes/entity.hpp"
#include "inexor/classes/selinfo.hpp"
#include "inexor/classes/extentity.hpp"
#include "inexor/classes/physent.hpp"
#include "inexor/classes/dynent.hpp"

#include "inexor/classes/cubescript/ident.hpp"
#include "inexor/classes/cubescript/identstack.hpp"
#include "inexor/classes/cubescript/tagval.hpp"
#include "inexor/classes/cubescript/nullval.hpp"

#include "inexor/macros/cubescript/identfun.hpp"


extern int curtime;                     // current frame time
extern int lastmillis;                  // last time
extern int elapsedtime;                 // elapsed frame time
extern int totalmillis;                 // total elapsed time
extern uint totalsecs;
extern int gamespeed, paused;


// lightning
extern void lightent(extentity &e, float height = 8.0f);
extern void lightreaching(const vec &target, vec &color, vec &dir, bool fast = false, extentity *e = 0, float ambient = 0.4f);
extern entity *brightestlight(const vec &target, const vec &dir);


// rays
extern float raycube   (const vec &o, const vec &ray,     float radius = 0, int mode = RAY_CLIPMAT, int size = 0, extentity *t = 0);
extern float raycubepos(const vec &o, const vec &ray, vec &hit, float radius = 0, int mode = RAY_CLIPMAT, int size = 0);
extern float rayfloor  (const vec &o, vec &floor, int mode = 0, float radius = 0);
extern bool  raycubelos(const vec &o, const vec &dest, vec &hitpos);

extern SharedVar<int> thirdperson;
extern bool isthirdperson();

extern bool settexture(const char *name, int clamp = 0);

extern SharedVar<int> worldsize;


// octaedit
struct editinfo;
extern editinfo *localedit;

extern bool editmode;

extern int shouldpacktex(int index);
extern bool packeditinfo(editinfo *e, int &inlen, uchar *&outbuf, int &outlen);
extern bool unpackeditinfo(editinfo *&e, const uchar *inbuf, int inlen, int outlen);
extern void freeeditinfo(editinfo *&e);
extern void pruneundos(int maxremain = 0);
extern bool packundo(int op, int &inlen, uchar *&outbuf, int &outlen);
extern bool unpackundo(const uchar *inbuf, int inlen, int outlen);
extern bool noedit(bool view = false, bool msg = true);
extern void toggleedit(bool force = true);
extern void mpeditface(int dir, int mode, selinfo &sel, bool local);
extern void mpedittex(int tex, int allfaces, selinfo &sel, bool local);
extern bool mpedittex(int tex, int allfaces, selinfo &sel, ucharbuf &buf);
extern void mpeditmat(int matid, int filter, selinfo &sel, bool local);
extern void mpflip(selinfo &sel, bool local);
extern void mpcopy(editinfo *&e, selinfo &sel, bool local);
extern void mppaste(editinfo *&e, selinfo &sel, bool local);
extern void mprotate(int cw, selinfo &sel, bool local);
extern void mpreplacetex(int oldtex, int newtex, bool insel, selinfo &sel, bool local, bool update = true);
extern bool mpreplacetex(int oldtex, int newtex, bool insel, selinfo &sel, ucharbuf &buf);
extern void mpdelcube(selinfo &sel, bool local);
extern bool mpeditvslot(int delta, int allfaces, selinfo &sel, ucharbuf &buf);
extern void mpremip(bool local);


// texture
class VSlot;
extern void packvslot(vector<uchar> &buf, int index);
extern void packvslot(vector<uchar> &buf, const VSlot *vs);


// command
extern int variable(const char *name, int min, int cur, int max, SharedVar<int> *storage, identfun fun, int flags);
extern float fvariable(const char *name, float min, float cur, float max, SharedVar<float> *storage, identfun fun, int flags);
extern char *svariable(const char *name, const char *cur, SharedVar<char*> *storage, identfun fun, int flags);
extern void setvar(const char *name, int i, bool dofunc = true, bool doclamp = true);
extern void setfvar(const char *name, float f, bool dofunc = true, bool doclamp = true);
extern void setsvar(const char *name, const char *str, bool dofunc = true);
extern void setvarchecked(ident *id, int val);
extern void setfvarchecked(ident *id, float val);
extern void setsvarchecked(ident *id, const char *val);
extern void touchvar(const char *name);
extern int getvar(const char *name);
extern int getvarmin(const char *name);
extern int getvarmax(const char *name);
extern bool identexists(const char *name);
extern ident *getident(const char *name);
extern ident *newident(const char *name, int flags = 0);
extern ident *readident(const char *name);
extern ident *writeident(const char *name, int flags = 0);
extern bool addcommand(const char *name, identfun fun, const char *narg);
extern bool addkeyword(int type, const char *name);
extern uint *compilecode(const char *p);
extern void keepcode(uint *p);
extern void freecode(uint *p);
extern void executeret(const uint *code, tagval &result = *commandret);
extern void executeret(const char *p, tagval &result = *commandret);
extern char *executestr(const uint *code);
extern char *executestr(const char *p);
extern int execute(const uint *code);
extern int execute(const char *p);
extern bool executebool(const uint *code);
extern bool executebool(const char *p);
extern bool execfile(const char *cfgfile, bool msg = true);
extern const char *getcurexecdir();
extern void alias(const char *name, const char *action);
extern void alias(const char *name, tagval &v);
extern const char *getalias(const char *name);
extern const char *escapestring(const char *s);
extern const char *escapeid(const char *s);
static inline const char *escapeid(ident &id) { return escapeid(id.name); }
extern bool validateblock(const char *s);
extern void explodelist(const char *s, vector<char *> &elems, int limit = -1);
extern char *indexlist(const char *s, int pos);
extern int listlen(const char *s);
extern void printvar(ident *id);
extern void printvar(ident *id, int i);
extern void printfvar(ident *id, float f);
extern void printsvar(ident *id, const char *s);
extern int clampvar(ident *id, int i, int minval, int maxval);
extern float clampfvar(ident *id, float f, float minval, float maxval);
extern void loopiter(ident *id, identstack &stack, const tagval &v);
extern void loopend(ident *id, identstack &stack);

#define loopstart(id, stack) if((id)->type != ID_ALIAS) return; identstack stack;
static inline void loopiter(ident *id, identstack &stack, int i) { tagval v; v.setint(i); loopiter(id, stack, v); }
static inline void loopiter(ident *id, identstack &stack, float f) { tagval v; v.setfloat(f); loopiter(id, stack, v); }
static inline void loopiter(ident *id, identstack &stack, const char *s) { tagval v; v.setstr(newstring(s)); loopiter(id, stack, v); }


// menus
extern vec menuinfrontofplayer();
extern void newgui(char *name, char *contents, char *header = NULL, char *init = NULL);
extern void showgui(const char *name);
extern int cleargui(int n = 0);


// octa
extern int lookupmaterial(const vec &o);

static inline bool insideworld(const vec &o)
{
    return o.x>=0 && o.x<worldsize && o.y>=0 && o.y<worldsize && o.z>=0 && o.z<worldsize;
}

static inline bool insideworld(const ivec &o)
{
    return uint(o.x)<uint(worldsize) && uint(o.y)<uint(worldsize) && uint(o.z)<uint(worldsize);
}


// world
extern bool emptymap(int factor, bool force, const char *mname = "", bool usecfg = true);
extern bool enlargemap(bool force);
extern int findentity(int type, int index = 0, int attr1 = -1, int attr2 = -1);
extern void findents(int low, int high, bool notspawned, const vec &pos, const vec &radius, vector<int> &found);
extern extentity *newentity(bool local, const vec &o, int type, int v1, int v2, int v3, int v4, int v5, int &idx);
extern void attachentity(extentity &e);
extern bool modifyoctaent(int flags, int id);
extern void mpeditent(int i, const vec &o, int type, int attr1, int attr2, int attr3, int attr4, int attr5, bool local);

extern vec getselpos();
extern int getworldsize();
extern int getmapversion();
extern void renderentcone(const extentity &e, const vec &dir, float radius, float angle);
extern void renderentarrow(const extentity &e, const vec &dir, float radius);
extern void renderentattachment(const extentity &e);
extern void renderentsphere(const extentity &e, float radius);
extern void renderentring(const extentity &e, float radius, int axis = 0);


// main
extern void fatal(const char *s, ...) PRINTFARGS(1, 2);


// rendertext
extern bool setfont(const char *name);
extern void pushfont();
extern bool popfont();
extern void gettextres(int &w, int &h);
extern void draw_text(const char *str, int left, int top, int r = 255, int g = 255, int b = 255, int a = 255, int cursor = -1, int maxwidth = -1);
extern void draw_textf(const char *fstr, int left, int top, ...) PRINTFARGS(1, 4);
extern float text_widthf(const char *str);
extern void text_boundsf(const char *str, float &width, float &height, int maxwidth = -1);
extern int text_visible(const char *str, float hitx, float hity, int maxwidth);
extern void text_posf(const char *str, int cursor, float &cx, float &cy, int maxwidth);

static inline int text_width(const char *str)
{
    return int(ceil(text_widthf(str)));
}

static inline void text_bounds(const char *str, int &width, int &height, int maxwidth = -1)
{
    float widthf, heightf;
    text_boundsf(str, widthf, heightf, maxwidth);
    width = int(ceil(widthf));
    height = int(ceil(heightf));
}

static inline void text_pos(const char *str, int cursor, int &cx, int &cy, int maxwidth)
{
    float cxf, cyf;
    text_posf(str, cursor, cxf, cyf, maxwidth);
    cx = int(cxf);
    cy = int(cyf);
}


// renderva
enum
{
    DL_SHRINK = 1<<0,
    DL_EXPAND = 1<<1,
    DL_FLASH  = 1<<2
};

extern void adddynlight(const vec &o, float radius, const vec &color, int fade = 0, int peak = 0, int flags = 0, float initradius = 0, const vec &initcolor = vec(0, 0, 0), physent *owner = NULL);
extern void dynlightreaching(const vec &target, vec &color, vec &dir, bool hud = false);
extern void removetrackeddynlights(physent *owner = NULL);


// rendergl
extern physent *camera1;
extern vec worldpos, camdir, camright, camup;

extern void disablezoom();

extern vec calcavatarpos(const vec &pos, float dist);
extern vec calcmodelpreviewpos(const vec &radius, float &yaw);

extern void damageblend(int n);
extern void damagecompass(int n, const vec &loc);

extern vec minimapcenter, minimapradius, minimapscale;
extern void bindminimap();

extern void bind_items_texture();
extern void bind_bomb_items_texture();

extern matrix4 hudmatrix;
extern void resethudmatrix();
extern void pushhudmatrix();
extern void flushhudmatrix(bool flushparams = true);
extern void pophudmatrix(bool flush = true, bool flushparams = true);
extern void pushhudscale(float sx, float sy = 0);
extern void pushhudtranslate(float tx, float ty, float sx = 0, float sy = 0);


// renderparticles
extern bool canaddparticles();
extern void regular_particle_splash(int type, int num, int fade, const vec &p, int color = 0xFFFFFF, float size = 1.0f, int radius = 150, int gravity = 2, int delay = 0);
extern void regular_particle_flame(int type, const vec &p, float radius, float height, int color, int density = 3, float scale = 2.0f, float speed = 200.0f, float fade = 600.0f, int gravity = -15);
extern void particle_splash(int type, int num, int fade, const vec &p, int color = 0xFFFFFF, float size = 1.0f, int radius = 150, int gravity = 2);
extern void particle_trail(int type, int fade, const vec &from, const vec &to, int color = 0xFFFFFF, float size = 1.0f, int gravity = 20);
extern void particle_text(const vec &s, const char *t, int type, int fade = 2000, int color = 0xFFFFFF, float size = 2.0f, int gravity = 0);
extern void particle_textcopy(const vec &s, const char *t, int type, int fade = 2000, int color = 0xFFFFFF, float size = 2.0f, int gravity = 0);
extern void particle_icon(const vec &s, int ix, int iy, int type, int fade = 2000, int color = 0xFFFFFF, float size = 2.0f, int gravity = 0);
extern void particle_meter(const vec &s, float val, int type, int fade = 1, int color = 0xFFFFFF, int color2 = 0xFFFFF, float size = 2.0f);
extern void particle_flare(const vec &p, const vec &dest, int fade, int type, int color = 0xFFFFFF, float size = 0.28f, physent *owner = NULL);
extern void particle_fireball(const vec &dest, float max, int type, int fade = -1, int color = 0xFFFFFF, float size = 4.0f);
extern void removetrackedparticles(physent *owner = NULL);


// decals
extern void adddecal(int type, const vec &center, const vec &surface, float radius, const bvec &color = bvec(0xFF, 0xFF, 0xFF), int info = 0);


// worldio
extern bool load_world(const char *mname, const char *cname = NULL);
extern bool save_world(const char *mname, bool nolms = false);
extern void getmapfilename(const char *fname, const char *cname, char *mapname);
extern uint getmapcrc();
extern void clearmapcrc();
extern bool loadents(const char *fname, vector<entity> &ents, uint *crc = NULL);


// physics
extern vec collidewall;
extern bool collideinside;
extern physent *collideplayer;
extern void moveplayer(physent *pl, int moveres, bool local);
extern bool moveplayer(physent *pl, int moveres, bool local, int curtime);
extern bool ellipseboxcollide(physent *d, const vec &dir, const vec &o, const vec &center, float yaw, float xr, float yr, float hi, float lo);
extern bool ellipsecollide(physent *d, const vec &dir, const vec &o, const vec &center, float yaw, float xr, float yr, float hi, float lo);
extern bool collide(physent *d, const vec &dir = vec(0, 0, 0), float cutoff = 0.0f, bool playercol = true);
extern bool bounce(physent *d, float secs, float elasticity, float waterfric, float grav);
extern bool bounce(physent *d, float elasticity, float waterfric, float grav);
extern void avoidcollision(physent *d, const vec &dir, physent *obstacle, float space);
extern bool overlapsdynent(const vec &o, float radius);
extern bool movecamera(physent *pl, const vec &dir, float dist, float stepdist);
extern void physicsframe();
extern void dropenttofloor(entity *e);
extern bool droptofloor(vec &o, float radius, float height);
extern void vecfromyawpitch(float yaw, float pitch, int move, int strafe, vec &m);
extern void vectoyawpitch(const vec &v, float &yaw, float &pitch);
extern bool moveplatform(physent *p, const vec &dir);
extern void updatephysstate(physent *d);
extern void cleardynentcache();
extern void updatedynentcache(physent *d);
extern bool entinmap(dynent *d, bool avoidplayers = false);
extern void findplayerspawn(dynent *d, int forceent = -1, int tag = 0);


// sound
enum
{
    SND_MAP = 1<<0
};

namespace inexor {
namespace sound {

    extern int playsound(int n, const vec *loc = NULL, extentity *ent = NULL, int flags = 0, int loops = 0, int fade = 0, int chanid = -1, int radius = 0, int expire = -1);
    extern int playsoundname(const char *s, const vec *loc = NULL, int vol = 0, int flags = 0, int loops = 0, int fade = 0, int chanid = -1, int radius = 0, int expire = -1);
    extern void preloadsound(int n);
    extern void preloadmapsound(int n);
    extern bool stopsound(int n, int chanid, int fade = 0);
    extern void stopsounds();
    extern void initsound();

}
}


// rendermodel
#include "inexor/classes/modelattach.hpp"

extern void startmodelbatches();
extern void endmodelbatches();
extern void rendermodel(entitylight *light, const char *mdl, int anim, const vec &o, float yaw = 0, float pitch = 0, int cull = MDL_CULL_VFC | MDL_CULL_DIST | MDL_CULL_OCCLUDED | MDL_LIGHT, dynent *d = NULL, modelattach *a = NULL, int basetime = 0, int basetime2 = 0, float trans = 1);
extern void abovemodel(vec &o, const char *mdl);
extern void rendershadow(dynent *d);
extern void renderclient(dynent *d, const char *mdlname, modelattach *attachments, int hold, int attack, int attackdelay, int lastaction, int lastpain, float fade = 1, bool ragdoll = false);
extern void interpolateorientation(dynent *d, float &interpyaw, float &interppitch);
extern void setbbfrommodel(dynent *d, const char *mdl);
extern const char *mapmodelname(int i);
extern model *loadmodel(const char *name, int i = -1, bool msg = false);
extern void preloadmodel(const char *name);
extern void flushpreloadedmodels(bool msg = true);

// ragdoll
extern void moveragdoll(dynent *d);
extern void cleanragdoll(dynent *d);

extern SharedVar<int> maxclients;

extern void *getclientinfo(int i);
extern ENetPeer *getclientpeer(int i);
extern ENetPacket *sendf(int cn, int chan, const char *format, ...);
extern ENetPacket *sendfile(int cn, int chan, stream *file, const char *format = "", ...);
extern void sendpacket(int cn, int chan, ENetPacket *packet, int exclude = -1);
extern void flushserver(bool force);
extern int getservermtu();
extern int getnumclients();
extern uint getclientip(int n);
extern void localconnect();
extern const char *disconnectreason(int reason);
extern void disconnect_client(int n, int reason);
extern void kicknonlocalclients(int reason = DISC_NONE);
extern bool hasnonlocalclients();
extern bool haslocalclients();
extern void sendserverinforeply(ucharbuf &p);
extern bool requestmaster(const char *req);
extern bool requestmasterf(const char *fmt, ...) PRINTFARGS(1, 2);
extern bool isdedicatedserver();


// client
extern void sendclientpacket(ENetPacket *packet, int chan);
extern void flushclient();
extern void disconnect(bool async = false, bool cleanup = true);
extern bool isconnected(bool attempt = false, bool local = true);
extern const ENetAddress *connectedpeer();
extern bool multiplayer(bool msg = true);
extern void neterr(const char *s, bool disc = true);
extern void gets2c();
extern void notifywelcome();


// crypto
extern void genprivkey(const char *seed, vector<char> &privstr, vector<char> &pubstr);
extern bool hashstring(const char *str, char *result, int maxlen);
extern void answerchallenge(const char *privstr, const char *challenge, vector<char> &answerstr);
extern void *parsepubkey(const char *pubstr);
extern void freepubkey(void *pubkey);
extern void *genchallenge(void *pubkey, const void *seed, int seedlen, vector<char> &challengestr);
extern void freechallenge(void *answer);
extern bool checkchallenge(const char *answerstr, void *correct);


// 3dgui
extern void g3d_addgui(g3d_callback *cb, vec &origin, int flags = 0);
extern bool g3d_movecursor(int dx, int dy);
extern void g3d_cursorpos(float &x, float &y);
extern void g3d_resetcursor();
extern void g3d_limitscale(float scale);
