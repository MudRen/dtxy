#include <armor.h>

#include <ansi.h>
inherit WRISTS;

void create()
{
  set_name("�̽�����", ({ "liujin wanlian", "wanlian", "wrists" }));
  set("weight", 200);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("long", "������ҵ����棶��������
    1������Ь
    2������
    3����ȹ��
    4�����
    5������
    6����ʯ��ָ
Ȼ��Ϳ���ΪŮ����÷ԧ�춨��(dingzhi)һ�׼��¡�\n");
    set("unit", "��");
    set("value", 5000);
    set("material", "gold");
    set("armor_prop/armor", 1);
  }
  setup();
}

void init()
{
  if(this_player()==environment())
  add_action("do_dingzhi","dingzhi");
}

int do_dingzhi()
{
int i,geng=0,jiding=0,dusi=0,zhugan=0,dongsun=0,shucai=0;
object jiayi,me, *inv;
object geng1,jiding1,dusi1,zhugan1,dongsun1,shucai1;
me = this_player();

inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                {
                        if(inv[i]->query("name") == HIR"����"NOR) {geng = 1; geng1 = inv[i];}
                        if(inv[i]->query("name") == RED"����Ь"NOR) {jiding = 1; jiding1 = inv[i];}
                        if(inv[i]->query("name") == "��ȹ��") {dusi = 1; dusi1 = inv[i];}
                        if(inv[i]->query("name") == "���") {zhugan = 1;  zhugan1 = inv[i];}
                        if(inv[i]->query("name") == "����") {dongsun = 1; dongsun1 = inv[i];}
                        if(inv[i]->query("name") == "��ʯ��ָ") {shucai = 1; shucai1 = inv[i];}
                        
                        
                        
                }
if( geng && jiding && dusi && zhugan && dongsun && shucai)
{
        destruct(geng1);
        destruct(jiding1);
        destruct(dusi1);
        destruct(zhugan1);
        destruct(dongsun1);
        destruct(shucai1);
        
        jiayi = new("/d/city/obj/jiayi");
        jiayi->move(me);
message_vision("$N�а����۵ذ��¡�ȹ������������һ�׼��£�\n",this_player());
        
        destruct(this_object());

}
else 
message_vision("$N��������ЩŮ���Ҷ��������ú��㡣\n",this_player());

return 1;
}
