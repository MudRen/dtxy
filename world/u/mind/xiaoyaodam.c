//Cracked by Roath
// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
inherit ITEM;

void create()
{
    set_name("��ң��", ({ "xiaoyao dan" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "��");
            set("material", "stone");
            set("long", "һ��������Ů���ã��ﵽ���ֵ���ң��.
            1��ҩ��
            2��������
            3����������
            4���ٻ���
Ȼ��Ϳ�����ҩ��(baoguo)��һ����������ҩ�������ǽ���Ů�Ĺ뷿˽�\n");
            set("owner_name","���湫��");
                     set("owner_id","yumian gongzhu");
          }

    setup();
}




void init()
{
  if(this_player()==environment())
  add_action("do_baoguo","baoguo");
}

int do_baoguo()
{
int i,geng=0,jiding=0,dusi=0,niang=0;
object shengsibu,me, *inv;
object geng1,jiding1,dusi1,niang1;
me = this_player();

inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                {
                        if(inv[i]->query("name") == "ҩ��") {geng = 1; geng1 = inv[i];}
                        if(inv[i]->query("name") == "������") {jiding = 1; jiding1 = inv[i];}
                        if(inv[i]->query("name") == "��������") {dusi = 1; dusi1 = inv[i];}
                        if(inv[i]->query("name") == "�ٻ���") {niang = 1; niang1 = inv[i];}
                        
                        }
if( geng && jiding && dusi && niang)
{
        destruct(geng1);
        destruct(jiding1);
        destruct(dusi1);
        destruct(niang1);
        shengsibu = new("/d/city/obj/shengsibu");
        shengsibu->move(me);
message_vision("$N�Ѽ�����������ҩ���ϣ�����ϸϸ�ذ����ã�\n",this_player());
        
        destruct(this_object());

}
else 
message_vision("$N������Щ���������࣮\n",this_player());

return 1;
}
