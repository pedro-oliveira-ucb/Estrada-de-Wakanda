#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cidades.h"

static int compare_cidades( const void * a , const void * b ) {
    const Cidade * ca = ( const Cidade * ) a;
    const Cidade * cb = ( const Cidade * ) b;
    return ca->Posicao - cb->Posicao;
}

Estrada * getEstrada( const char * nomeArquivo ) {
    FILE * file = fopen( nomeArquivo , "r" );
    if ( !file ) return NULL;

    char buffer[ 256 ];
    int T , N;

  
    if ( !fgets( buffer , sizeof( buffer ) , file ) || sscanf( buffer , "%d" , &T ) != 1 ) {
        fclose( file );
        return NULL;
    }
    // Validar T: 3 ≤ T ≤ 1e6
    if ( T < 3 || T > 1e6 ) {
        fclose( file );
        return NULL;
    }

  
    if ( !fgets( buffer , sizeof( buffer ) , file ) || sscanf( buffer , "%d" , &N ) != 1 ) {
        fclose( file );
        return NULL;
    }
    // Validar N: 2 ≤ N ≤ 1e4
    if ( N < 2 || N > 1e4 ) {
        fclose( file );
        return NULL;
    }

    Cidade * cidades = malloc( N * sizeof( Cidade ) );
    if ( !cidades ) {
        fclose( file );
        return NULL;
    }

    for ( int i = 0; i < N; i++ ) {
        if ( !fgets( buffer , sizeof( buffer ) , file ) ) {
            free( cidades );
            fclose( file );
            return NULL;
        }

        int xi;
        char nome[ 256 ];
    
        if ( sscanf( buffer , "%d %255[^\n]" , &xi , nome ) != 2 ) {
            free( cidades );
            fclose( file );
            return NULL;
        }

        // Validar posição: 0 < Xi < T
        if ( xi <= 0 || xi >= T ) {
            free( cidades );
            fclose( file );
            return NULL;
        }

        cidades[ i ].Posicao = xi;
        strncpy( cidades[ i ].Nome , nome , 255 );
        cidades[ i ].Nome[ 255 ] = '\0'; // Garantir término da string
    }

 
    qsort( cidades , N , sizeof( Cidade ) , compare_cidades );

    // Verificar posições duplicadas após ordenação
    for ( int i = 1; i < N; i++ ) {
        if ( cidades[ i ].Posicao == cidades[ i - 1 ].Posicao ) {
            free( cidades );
            fclose( file );
            return NULL;
        }
    }

    // Criar estrutura Estrada
    Estrada * e = malloc( sizeof( Estrada ) );
    if ( !e ) {
        free( cidades );
        fclose( file );
        return NULL;
    }

    e->T = T;
    e->N = N;
    e->C = cidades;

    fclose( file );
    return e;
}

double calcularMenorVizinhanca( const char * nomeArquivo ) {
    Estrada * e = getEstrada( nomeArquivo );
    if ( !e ) return 0.0;

    double menor_vizinhanca = INFINITY;
    int N = e->N;
    Cidade * c = e->C;
    int T = e->T;

    for ( int i = 0; i < N; i++ ) {
        double left , right;

        if ( i == 0 ) {
            left = 0.0;
            right = ( c[ i ].Posicao + c[ i + 1 ].Posicao ) / 2.0;
        }
        else if ( i == N - 1 ) {
            left = ( c[ i - 1 ].Posicao + c[ i ].Posicao ) / 2.0;
            right = ( double ) T;
        }
        else {
            left = ( c[ i - 1 ].Posicao + c[ i ].Posicao ) / 2.0;
            right = ( c[ i ].Posicao + c[ i + 1 ].Posicao ) / 2.0;
        }

        double vizinhanca = right - left;
        if ( vizinhanca < menor_vizinhanca ) {
            menor_vizinhanca = vizinhanca;
        }
    }

    free( e->C );
    free( e );
    return menor_vizinhanca;
}

char * cidadeMenorVizinhanca( const char * nomeArquivo ) {
    Estrada * e = getEstrada( nomeArquivo );
    if ( !e ) return NULL;

    double menor_vizinhanca = INFINITY;
    int index = 0;
    int N = e->N;
    Cidade * c = e->C;
    int T = e->T;

    for ( int i = 0; i < N; i++ ) {
        double left , right;

        if ( i == 0 ) {
            left = 0.0;
            right = ( c[ i ].Posicao + c[ i + 1 ].Posicao ) / 2.0;
        }
        else if ( i == N - 1 ) {
            left = ( c[ i - 1 ].Posicao + c[ i ].Posicao ) / 2.0;
            right = ( double ) T;
        }
        else {
            left = ( c[ i - 1 ].Posicao + c[ i ].Posicao ) / 2.0;
            right = ( c[ i ].Posicao + c[ i + 1 ].Posicao ) / 2.0;
        }

        double vizinhanca = right - left;
        if ( vizinhanca < menor_vizinhanca ) {
            menor_vizinhanca = vizinhanca;
            index = i;
        }
    }

    char * nome = malloc( 256 * sizeof( char ) );
    if ( !nome ) {
        free( e->C );
        free( e );
        return NULL;
    }

    strncpy( nome , c[ index ].Nome , 255 );
    nome[ 255 ] = '\0'; // Garantir término da string

    free( e->C );
    free( e );
    return nome;
}