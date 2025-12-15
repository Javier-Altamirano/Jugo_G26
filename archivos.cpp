#include "archivos.h"
#include <fstream>
using namespace std;
///-----------> ITEMS <-----------///
bool Archivos::GuardarItem(const Item& reg)
{
    FILE *p = fopen(_items.c_str(), "ab");
    if(p == NULL)
    {
        cout << "No se pudo abrir\n";
        return false;
    }
    bool ok = fwrite(&reg, sizeof(Item),1, p);
    fclose(p);
    return ok;
}
bool Archivos::ReGuardarItem(const Item& reg, int pos)
{
    FILE *p = fopen(_items.c_str(), "rb+");
    if(p == NULL)
    {
        cout << "No se pudo abrir\n";
        return false;
    }
    fseek(p, sizeof(Item) * pos, SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Item), 1, p);
    fclose(p);
    return ok;
}
Item Archivos::LeerItem(int pos)
{
    FILE *p = fopen(_items.c_str(), "rb");
    if(p == NULL)
    {
        cout << "No se pudo abrir\n";
        return Item();
    }
    Item reg;
    fseek(p, sizeof(Item) * pos, SEEK_SET);
    fread(&reg,sizeof(Item), 1, p);
    fclose(p);
    return reg;
}
int Archivos::CantItemsG()
{
    FILE *p = fopen(_items.c_str(), "rb");
    if(p == NULL)
    {
        cout << "No se pudo abrir\n";
        return 0;
    }
    fseek(p, 0, SEEK_END);
    int cantidad = ftell(p) / sizeof(Item);
    fclose(p);
    return cantidad;
}
int Archivos::BII(int id)
{
    FILE *p = fopen(_items.c_str(), "rb");
    if(p == NULL)
    {
        return -1;
    }
    Item reg;
    int i=0;

    while(fread(&reg, sizeof(Item), 1, p))
    {
        if(reg.getId() == id)
        {
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}
void Archivos::LeerIT(Item* v, int cantidad)
{
    FILE *p = fopen(_items.c_str(), "rb");
    if(p == NULL)
    {
        return;
    }
    for(int i=0; i < cantidad; i++)
    {
        if (fread(&v[i], sizeof(Item), 1, p) != 1)
        {
            break;
        }
    }
    fclose(p);
}
//-----------> JUGABLES <-----------///
bool Archivos::GuardarAliados(const Aliado& reg)
{
    FILE *p = fopen(_aliados.c_str(), "ab");
    if(p == NULL)
    {
        cout << "No se abrio\n";
        return false;
    }
    bool ok = fwrite(&reg, sizeof(Aliado), 1, p);
    fclose(p);
    return ok;
}
bool Archivos::ReGuardarAliados(const Aliado& reg, int pos)
{
    FILE *p = fopen(_aliados.c_str(), "rb+");
    if(p == NULL)
    {
        cout << "No se abrio\n";
        return false;
    }
    fseek(p, sizeof(Aliado) * pos, SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Aliado), 1, p);
    fclose(p);
    return ok;
}
Aliado Archivos::LeerAliado(int pos)
{
    FILE *p = fopen(_aliados.c_str(), "rb");
    if(p == NULL)
    {
        cout << "No se abrio\n";
        return Aliado();
    }
    Aliado reg;
    fseek(p, sizeof(Aliado) * pos, SEEK_SET);
    fread(&reg,sizeof(Aliado), 1, p);
    fclose(p);
    return reg;
}
int Archivos::CantAliadoG()
{
    FILE *p = fopen(_aliados.c_str(), "rb");
    if(p == NULL)
    {
        cout << "No se abrio\n";
        return 0;
    }
    fseek(p, 0, SEEK_END);
    int cantidad = ftell(p) / sizeof(Aliado);
    fclose(p);
    return cantidad;
}
int Archivos::BIA(int id)
{
    FILE *p = fopen(_aliados.c_str(), "rb");
    if(p == NULL)
    {
        cout << "No se abrio\n";
        return -1;
    }
    Aliado reg;
    int i = 0;
    while(fread(&reg, sizeof(Aliado),1,p))
    {
        if(reg.getId() == id)
        {
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}
void Archivos::LeerAT(Aliado* v, int cantidad)
{
    FILE *p = fopen(_aliados.c_str(), "rb");
    if(p == NULL)
    {
        cout << "No se abrio\n";
        return;
    }
    for(int i=0; i<cantidad; i++)
    {
        if (fread(&v[i], sizeof(Aliado), 1, p) != 1)
        {
            break;
        }
    }
    fclose(p);
}
//-----------> ENEMIGOS <-----------///
bool Archivos::GuardarEnemigo(const Enemigos& reg)
{
    FILE *p = fopen(_enemigos.c_str(), "ab");
    if(p == NULL)
    {
        cout << "no se abrio\n";
        return false;
    }
    bool ok = fwrite(&reg, sizeof(Enemigos), 1, p);
    fclose(p);
    return ok;
}
bool Archivos::ReGuardarEnemigo(const Enemigos& reg, int pos)
{
    FILE *p = fopen(_enemigos.c_str(), "rb+");
    if(p == NULL)
    {
        cout << "no se abrio\n";
        return false;
    }
    fseek(p, sizeof(Enemigos) * pos, SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Enemigos), 1, p);
    fclose(p);
    return ok;
}
Enemigos Archivos::LeerEnemigo(int pos)
{
    FILE *p = fopen(_enemigos.c_str(), "rb");
    if(p == NULL)
    {
        cout << "no se abrio\n";
        return Enemigos();
    }
    Enemigos reg;
    fseek(p, sizeof(Enemigos) * pos, SEEK_SET);
    fread(&reg, sizeof(Enemigos), 1, p);
    fclose(p);
    return reg;
}
int Archivos::CantEnemigoG()
{
    FILE *p = fopen(_enemigos.c_str(), "rb");
    if(p == NULL)
    {
        cout << "no se abrio\n";
        return 0;
    }
    fseek(p, 0,SEEK_END);
    int cantidad = ftell(p) / sizeof(Enemigos);
    fclose(p);
    return cantidad;
}
int Archivos::BIE(int id)
{
    FILE *p = fopen(_enemigos.c_str(), "rb");
    if(p == NULL)
    {
        cout << "no se abrio\n";
        return -1;
    }
    Enemigos reg;
    int i = 0;
    while(fread(&reg, sizeof(Enemigos), 1, p))
    {
        if(id == reg.getId())
        {
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}
void Archivos::LeerET(Enemigos* v, int cantidad)
{
    FILE *p = fopen(_enemigos.c_str(), "rb");
    if(p == NULL)
    {
        cout << "no se abrio\n";
        return;
    }
    for(int i=0; i<cantidad; i++)
    {
        if (fread(&v[i], sizeof(Enemigos), 1, p) != 1)
        {
            break;
        }
    }
    fclose(p);
}
