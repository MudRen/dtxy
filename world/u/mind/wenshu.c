//Cracked by Roath
// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
inherit ITEM;
void create()
{
        set_name("����", ({"wen shu", "shu"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "����˾���������������������顣������ҵ����棳��������
                1���廨��
                2��������
                3���鲼ͷ
Ȼ��Ϳ��Զ�(ding)��һ������������������������������Ҫ����ʲ��\n");
                set("unit", "��");
               set("owner_name","������");
               set("owner_id","yin changsheng");
        }
}

void init()
{
  if(this_player()==environment())
  add_action("do_ding","ding");
}

int do_ding()
{
int i,geng=0,jiding=0,dusi=0;
object shengsibu,me, *inv;
object geng1,jiding1,dusi1;
me = this_player();

inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                {
                        if(inv[i]->query("name") == "�廨��") {geng = 1; geng1 = inv[i];}
                        if(inv[i]->query("name") == "������") {jiding = 1; jiding1 = inv[i];}
                        if(inv[i]->query("name") == "�鲼ͷ") {dusi = 1; dusi1 = inv[i];}
                        
                        
                        }
if( geng && jiding && dusi)
{
        destruct(geng1);
        destruct(jiding1);
        destruct(dusi1);
        
        shengsibu = new("/d/city/obj/shengsibu");
        shengsibu->move(me);
message_vision("$N�����廨�룬ϸ�ĵ��޲����ˡ���������������\n",this_player());
        
        destruct(this_object());

}
else 
message_vision("$NŪ�������Щ������ʲô��;��\n",this_player());

return 1;
}
