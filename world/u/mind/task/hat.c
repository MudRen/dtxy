// /d/gao/obj/hat.c

#include <armor.h>

inherit HEAD;

void create()
{
        set_name("ձñ", ({ "hat" }) );
        set_weight(800);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                


        set("long", "һ����ͨ��ñ�ӣ�������ҵ����棴��������
    1����Ƥñ
    2����˿ñ
    3��ţƤñ
    4��ɵñ
Ȼ��Ϳ����ð�(zhiban)��һ������ñ�����õ��������ʮ�ֺ��\n");
                set("unit", "��");
                set("material", "cloth");
                set("value", 100);
                set("armor_prop/armor", 2);
        }
        setup();
}


void init()
{
  if(this_player()==environment())
  add_action("do_zhiban","zhiban");
}

int do_zhiban()
{
int i,geng=0,jiding=0,dusi=0,zhugan=0;
object minmao,me, *inv;
object geng1,jiding1,dusi1,zhugan1;
me = this_player();

inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                {
                        if(inv[i]->query("name") == "��Ƥñ") {geng = 1; geng1 = inv[i];}
                        if(inv[i]->query("name") == "��˿ñ") {jiding = 1; jiding1 = inv[i];}
                        if(inv[i]->query("name") == "ţƤñ") {dusi = 1; dusi1 = inv[i];}
                        if(inv[i]->query("name") == "ɵñ") {zhugan = 1;  zhugan1 = inv[i];}
                        

                }
if( geng && jiding && dusi && zhugan)
{
        destruct(geng1);
        destruct(jiding1);
        destruct(dusi1);
        destruct(zhugan1);
        
        minmao = new("/d/city/obj/minmao");
        minmao->move(me);
message_vision("$N����Щñ�ӷ��������һ���ð���һ������ñ��\n",this_player());
        
        destruct(this_object());

}
else 
message_vision("$N������Щñ�Ӳ����ÿ���������Ȥ��\n",this_player());

return 1;
}
