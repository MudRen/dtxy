
//ȭ����
inherit ITEM;
void create()
{
        set_name("��ȭ�����š�", ({"quan ji", "book"}));
        set_weight(1000);
        if( clonep() )
        set_default_object(__FILE__);
        else {
        set("unit", "��");
        set("value", 100);
  set("long",
"һ��������С���ӣ�\n��˵���������������\n��������\n");
        set("material", "paper");
        set("skill", ([
                        "name": "boxing",
                        "sen_cost": 10,
                        "difficulty": 10,
                        "max_skill": 100,
]) );
        }
}

