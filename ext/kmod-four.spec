Name:           kmod-four
Version:        
Release:        1%{?dist}
Summary:        Linux kernel module for high throughput RFC1149.5-compliant random number generation.

License:        
URL:            
Source0:        

BuildRequires:  kernel-devel
Requires:       

%description
Linux kernel module for high throughput RFC1149.5-compliant random number generation.

%prep
%setup -q


%build
%configure
make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT


%files
%doc



%changelog
