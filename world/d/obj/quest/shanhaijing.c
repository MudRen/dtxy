//Cracked by Roath
// literate.c

inherit ITEM;

void create()
{
        set_name("��ɽ������", ({"shanhai jing", "jing"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 200);
        set("long",
"һ��������С���ӣ��ƹ������˽�ϲ�������ɹ�ֿ��\n��������\n");
        set("material", "paper");
        set("owner_name", "��������");
          set("owner_id", "lao ren");
        set("skill", ([
                        "name": "literate",
                        "sen_cost": 45,
                        "difficulty": 40,
                        "max_skill": 60,
]) );
        }
}
