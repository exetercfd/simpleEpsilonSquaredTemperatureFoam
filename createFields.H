    Info<< "Reading field p\n" << endl;
    volScalarField p
    (
        IOobject
        (
            "p",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    Info<< "Reading field U\n" << endl;
    volVectorField U
    (
        IOobject
        (
            "U",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );
    
    Info<< "Reading field T\n" << endl;
    volScalarField T
    (
        IOobject
        (
            "T",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    #include "createPhi.H"


    label pRefCell = 0;
    scalar pRefValue = 0.0;
    setRefCell(p, mesh.solutionDict().subDict("SIMPLE"), pRefCell, pRefValue);

    singlePhaseTransportModel laminarTransport(U, phi);

    Info<< "Reading transportProperties\n" << endl;

    IOdictionary transportProperties
    (
        IOobject
	(
	    "transportProperties",
	    runTime.constant(),
	    mesh,
	    IOobject::MUST_READ,
	    IOobject::NO_WRITE
	)
    );

    Info<< "Reading fluid kinematic viscosity nu\n" << endl;

    dimensionedScalar nu
    (
        transportProperties.lookup("nu")
    );

    Info<< "Reading porosity eps\n" << endl;

    dimensionedScalar eps
    (
        transportProperties.lookup("eps")
    );
    
    Info<< "Reading effective fluid conductivity kfe\n" << endl;

    dimensionedScalar kfe
    (
        transportProperties.lookup("kfe")
    );
    
    Info<< "Reading effective solid conductivity kse\n" << endl;

    dimensionedScalar kse
    (
        transportProperties.lookup("kse")
    );    
    
    Info<< "Reading fluid density rhof\n" << endl;

    dimensionedScalar rhof
    (
        transportProperties.lookup("rhof")
    );
    
    Info<< "Reading fluid specific heat capacity cpf\n" << endl;

    dimensionedScalar cpf
    (
        transportProperties.lookup("cpf")
    );
    
    autoPtr<incompressible::RASModel> turbulence
    (
        incompressible::RASModel::New(U, phi, laminarTransport)
    );
