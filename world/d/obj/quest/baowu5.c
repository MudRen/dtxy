//Cracked by Roath
// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
inherit ITEM;

void create()
{
        set_name("���Լ�", ({"jinjiao jian","jian"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "�˼�������������������������������¾��������ڿ��У��������£�\n���ƻ��壬ͷ��ͷ�����β��β��ɣ�������õ����ɣ�һ�����Ρ�\n������ҵ����棲��������
    1��������
    2��������
Ȼ��Ϳ������(miaohui)��һ�ű���ͼ����\n");
                set("unit", "��");
                set("lingtaibao","fake");
                 set("owner_name","������ʦ");
                 set("owner_id","master puti");
        }
}

void init()
{
  if(this_player()==environment())
  add_action("do_miaohui","miaohui");
}

int do_miaohui()
{
int i,geng=0,jiding=0;
object tuer,me, *inv;
object geng1,jiding1;
me = this_player();

inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                {
                        if(inv[i]->query("name") == "������") {geng = 1; geng1 = inv[i];}
                        if(inv[i]->query("name") == "������") {jiding = 1; jiding1 = inv[i];}
                        }
if( geng && jiding)
{
        destruct(geng1);
        destruct(jiding1);
        tuer = new("/d/city/obj/tu_er");
        tuer->move(me);
message_vision("$N�ڱ�����������ҫ�£�����Щ��������һ�ű���ͼ�����üǺš�������\n",this_player());
        
        destruct(this_object());

}
else 
message_vision("$NĦ���ű���Ŀ�������\n",this_player());

return 1;
}
