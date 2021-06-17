inherit ROOM;
#include <ansi.h>
#include <race.h>

int block_cmd(string);
void create ()
{
  set ("short", "�ϳǿ�ջ");
  set ("long", @LONG

��ҿ�ջ�������������ģ���������ǳ���¡����֮��Ǯ����������
��������ο���ŵ���ѡ��¶������߰������ӣ����̾����˵��ڴ�
�������������ﲻ�����������õ�С�������ػ��д����ķ����͡���
¥���������������ǿͷ�����֪��Ϊ��ʲô, ż���������������ô�
��(dading)��
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
		return notify_fail("������æ!\n");
          if (player->query_temp("mod/level")) return notify_fail("������װ�ٴ򶥰ɣ�\n");
	busy = 4;
	message_vision(HIC"\n$N����������ֵ�����, ���������˴�...\n"NOR, player);
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
	message_vision(HIC"\n$N��������, һ������ı���\n"NOR, who);
	tell_object(who,"��ĸ���ָ�������,��hp�鿴\n");
}
// ends; emotion

int valid_leave(object me, string dir)
{
        object mbox;

        if ( !me->query_temp("rent_paid") && dir == "east" )
        return notify_fail("��С��������Ц�ص�ס���㣺�Բ��𣬺����ǿ��˵��Է������Ǳ���Ŀ��ˣ�������š�\n");
        if( mbox = me->query_temp("mbox_ob") ) {
                tell_object(me, "�㽫���佻�ظ��ʲ\n");
                destruct(mbox);
        }

        return ::valid_leave(me, dir);
}

