#include <weapon.h>

inherit SWORD;

void create()
{
        set_name("���ѩ�轣", ({ "snowsword", "xue jian", "sword" }) );
        set_weight(400);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 700);
                set("material", "steel");
                set("long", "����һ����������Ľ�������ϸ���������ȷ�����������ҵ����棷��������
    1����ǹ
    2����
    3��ԧ���
    4����β��
    5�����Ƶ�
    6���˰�÷����
    7��«����
Ȼ��Ϳ���������д(tengxie)��һ�������������ס�������ү��
ǧ���ټ���㵽�֡�\n");
                set("wield_msg", "$N���һ�ѽ���ϸ���Ľ����������С�\n");
                set("unequip_msg", "$N�������е�$n��\n");
                set("weapon_prop/courage", 4);
        }
        init_sword(40);
        setup();
}

void init()
{
  if(this_player()==environment())
  add_action("do_tengxie","tengxie");
}

int do_tengxie()
{
int i,geng=0,jiding=0,dusi=0,zhugan=0,dongsun=0,shucai=0,caomei=0;
object canpu,me, *inv;
object geng1,jiding1,dusi1,zhugan1,dongsun1,shucai1,caomei1;
me = this_player();

inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                {
                        if(inv[i]->query("name") == "��ǹ") {geng = 1; geng1 = inv[i];}
                        if(inv[i]->query("name") == "��") {jiding = 1; jiding1 = inv[i];}
                        if(inv[i]->query("name") == "ԧ���") {dusi = 1; dusi1 = inv[i];}
                        if(inv[i]->query("name") == "���Ƶ�") {zhugan = 1;  zhugan1 = inv[i];}
                        if(inv[i]->query("name") == "��β��") {dongsun = 1; dongsun1 = inv[i];}
                        if(inv[i]->query("name") == "�˰�÷����") {shucai = 1; shucai1 = inv[i];}
                        if(inv[i]->query("name") == "«����") {caomei = 1; caomei1 = inv[i];}
                        
                        
                }
if( geng && jiding && dusi && zhugan && dongsun && shucai && caomei)
{
        destruct(geng1);
        destruct(jiding1);
        destruct(dusi1);
        destruct(zhugan1);
        destruct(dongsun1);
        destruct(shucai1);
        destruct(caomei1);
        
        canpu = new("/d/city/obj/canpu");
        canpu->move(me);
message_vision("$N����С�Ǻ���һ˿�����ذ���Щ�����������α����һ�������������ף�\n",this_player());
        
        destruct(this_object());

}
else 
message_vision("$N�ջ�����Щ���������˵ص������Ρ�\n",this_player());

return 1;
}
