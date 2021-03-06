inherit ROOM;
#include <ansi.h>
#include <race.h>

int block_cmd(string);
void create ()
{
  set ("short", "南城客栈");
  set ("long", @LONG

这家客栈紧靠长安城中心，所以生意非常兴隆。兼之价钱低廉，更是
成了外地游客落脚的首选。露天摆了七八张桌子，三教九流人等在此
进进出出，络绎不绝，几个跑堂的小二来来回回招待着四方来客。二
楼上是雅厅，后面是客房。不知道为了什么, 偶尔会有人来这里拿大
顶(dading)。
LONG);
  set("exits", ([ /* sizeof() == 4 */
  "east" : __DIR__"sleep",
  "west" : __DIR__"zhuque-s1",
  "north" : __DIR__"giftroom",

  "up": "/d/wiz/entrance",
]));
   set("chat_room",1);
  set("objects", ([ /* sizeof() == 2 */
  __DIR__"npc/xiaoer" : 1,
"/d/ourhome/npc/bigeye" : 1,
  "/d/city/npc/bai" : 1,
"/d/city/npc/panguan":1,
"/d/ourhome/npc/seng" : 1,
]));
  set("no_time",1);

   set("no_time", 1);
  set("no_fight", 1);
  set("no_magic", 1);
        set("freeze",1);
  set("resource", ([ /* sizeof() == 1 */
  "water" : 1,
]));
  set("valid_startroom", 1);
  setup();
  call_other("/obj/board/nancheng_b", "???");
}

void init()
{
    add_action("block_cmd", "", 1);
    add_action("do_dading", "dading");  // emotion
}

int block_cmd(string args)
{
string verb;
verb = query_verb();

    // if (verb == "bian") return 1; // by mon 7/15
    if (verb == "xiudao") return 1;
    if (verb == "exert") return 1;
    return 0;
}

// begins:  emotion
int do_dading(string arg) {
	int busy;
	object player = this_player();
	if ( player->is_busy() )
		return notify_fail("你正在忙!\n");
          if (player->query_temp("mod/level")) return notify_fail("脱了套装再打顶吧！\n");
	busy = 4;
	message_vision(HIC"\n$N不顾众人奇怪的眼神, 当众拿起了大顶...\n"NOR, player);
	call_out("dading_done", busy, player );
	player->start_busy( busy );
	return 1;
}

void dading_done(object who) {
	int my_max_force, my_max_manna;
	/*my_max_force = who->query_max_force();
	my_max_manna = who->query_max_mana();
	who->set("max_force", my_max_force);
	who->set("max_mana", my_max_manna);
	if ( my_max_force > who->query("maximum_force") )
		who->set("maximum_force", my_max_force);
	else
		who->set("max_force", who->query("maximum_force") );
	if ( my_max_manna > who->query("maximum_mana") )
		who->set("maximum_mana", my_max_manna);
	else
		who->set("max_mana", who->query("maximum_mana"));
	*/
	//change buy kugu
	my_max_manna = who->query_skill("spells") * 10;
	my_max_force = who->query_skill("force") * 10;
	who->set("max_force", my_max_force);
	who->set("max_mana", my_max_manna);
	who->set("maximum_force", my_max_force);
	who->set("maximum_mana", my_max_manna);
	HUMAN_RACE->update_player_health(who);
	if( who->query("eff_kee") > who->query("max_kee") ) who->set("eff_kee",who->query("max_kee"));
	if( who->query("kee") > who->query("max_kee") ) who->set("kee",who->query("max_kee"));
	if( who->query("eff_sen") > who->query("max_sen") ) who->set("eff_sen",who->query("max_sen"));
	if( who->query("sen") > who->query("max_sen") ) who->set("sen",who->query("max_sen"));
	message_vision(HIC"\n$N翻身起来, 一副满足的表情\n"NOR, who);
	tell_object(who,"你的各项指标更新了,用hp查看\n");
}
// ends; emotion

int valid_leave(object me, string dir)
{
        object mbox;

        if ( !me->query_temp("rent_paid") && dir == "east" )
        return notify_fail("店小二满脸堆笑地挡住了你：对不起，后面是客人的卧房，不是本店的客人，不便打扰。\n");
        if( mbox = me->query_temp("mbox_ob") ) {
                tell_object(me, "你将信箱交回给邮差。\n");
                destruct(mbox);
        }

        return ::valid_leave(me, dir);
}

