inherit ROOM;

void create ()
{
  set ("short", "Ǳ�ܹ��н�����");
  set ("long", @LONG

�����Ǵ̼��ǳ���Ǳ�ܹ��н��������������������Ǳ�ܽ��й��н�
�ף������Ϸ��и�����(paizi)�����������й�Ʊ���ס����ڹ��б�
��Ī�⣬������Ҫ����������鿴�������������

LONG);
  set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"kezhan",
    
]));
   
  set("no_fight", 1);
  set("no_magic", 1);
  set("item_desc", ([ /* sizeof() == 1 */
  "paizi" : "
    �鿴��Ʊ���¼۸�check
    ������Ʊ��sell
    �����Ʊ��buy

"]));
  setup();
  
}

void init()
{
    add_action("do_check", "check");
    add_action("do_buy", "buy");
    add_action("do_sell","sell");
}

int do_check(string name)
{
	string output;
	output = "/adm/daemons/gushid"->gushi_list(name);
	this_player()->start_more(output);
        return 1;
}
        