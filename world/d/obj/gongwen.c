
#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(YEL"����"NOR, ({ "gong wen", "wen" }) );
	set("long", "����һ�ų������Ĺ��ġ�\n");
	set_weight(3000);
	set("unit", "��");
	setup();
}

string long()
{
	object target;
	
	if(this_player()!=query("master"))
		return "����һ�ų������Ĺ��ġ�\n";
	if(objectp(target=query("target")))
		return sprintf("����һ�Ż�����������͸�%s(%s)�Ĺ��ġ�\n"
			, YEL+target->name(1)+NOR, 
			capitalize(target->query("id")));
	return "����һ�ų������Ĺ��ġ�\n";
}
