inherit EQUIP;

void create()
{
  set_name("ϸ����¨", ({ "zhu lou","zhulou","lou","basket"}) );
  set_weight(500);
  set_max_encumbrance(8000);
  set_max_items(12);
  if( clonep() ){
    set_default_object(__FILE__);
  } else {
    set("unit", "ֻ");
    set("long", "����һֻƯ����ϸ����¨��������ҵ����棷��������
    1����ͷ
    2������
    3��������
    4����ɨ��
    5�����
    6������Ͳ
    7������
Ȼ��Ϳ���Ϊ���Ĵ峤����(gouzhi)��һ�״����Ͷ��õ�������ʲ��\n");
    set("value", 200);
  }
  set("armor_prop/armor", 1);
  set("armor_type", "basket");
  set("wear_msg", "$N����ϸ����¨�����ɵر������ϡ�\n");
  set("unequip_msg", "$N��ϸ����¨�ӱ���ж���������ڻ��\n");
}

void init()
{
  if(this_player()==environment())
  add_action("do_gouzhi","gouzhi");
}

int do_gouzhi()
{
int i,geng=0,jiding=0,dusi=0,zhugan=0,dongsun=0,shucai=0,caomei=0;
object wushi,me, *inv;
object geng1,jiding1,dusi1,zhugan1,dongsun1,shucai1,caomei1;
me = this_player();

inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                {
                        if(inv[i]->query("name") == "��ͷ") {geng = 1; geng1 = inv[i];}
                        if(inv[i]->query("name") == "����") {jiding = 1; jiding1 = inv[i];}
                        if(inv[i]->query("name") == "������") {dusi = 1; dusi1 = inv[i];}
                        if(inv[i]->query("name") == "���") {zhugan = 1;  zhugan1 = inv[i];}
                        if(inv[i]->query("name") == "����Ͳ") {dongsun = 1; dongsun1 = inv[i];}
                        if(inv[i]->query("name") == "��ɨ��") {shucai = 1; shucai1 = inv[i];}
                        if(inv[i]->query("name") == "����") {caomei = 1; caomei1 = inv[i];}
                        
                        
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
        
        wushi = new("/d/city/obj/wushi");
        wushi->move(me);
message_vision("$N������һЩ�ɻ����ʲ���Ž����\n",this_player());
        
        destruct(this_object());

}
else 
message_vision("$N��ֱ�������ӵܣ��㲻�����Щ������ɶ�ã�\n",this_player());

return 1;
}

