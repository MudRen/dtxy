//Cracked by Roath
// literate.c

inherit ITEM;

void create()
{
        set_name("������", ({"zhaoyao jing", "jing"}));
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                
        set("long",
"һ����ɫͭ�Ƶ���������ʹ���ϵ��µ���ħ����޴����Ρ�\n");
        set("material", "steel");
        set("owner_name", "�");
          set("owner_id", "li jing");
        set("skill", ([
                        "name": "literate",
                        "sen_cost": 45,
                        "difficulty": 40,
                        "max_skill": 60,
]) );
        }
}
