
#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(RED"�ܺ�"NOR, ({ "mi han", "han" }) );
	set("long", "����һ���ܺ���\n");
	set_weight(3000);
	set("unit", "��");
	setup();
}

string long()
{
	object target;
	
	if(this_player()!=query("master"))
		return "����һ���ܺ���\n";
	if(objectp(target=query("target")))
		return sprintf("����һ��̫ƽ���������͸�%s(%s)���ܺ���\n"
			, WHT+target->name(1)+NOR,
			capitalize(target->query("id")));
	return "����һ���ܺ���\n";
}
